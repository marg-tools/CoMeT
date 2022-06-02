#include <iostream>
using namespace std;
#include "dram_perf_model_variable.h"
#include "simulator.h"
#include "config.h"
#include "config.hpp"
#include "stats.h"
#include "shmem_perf.h"

#include "math.h" // included by leo for log2 but I don't know what that is used for

#define ENABLE_CHANNEL_PARTITIONING 0   // why is this here if it is always zero?


DramPerfModelVariable::DramPerfModelVariable(core_id_t core_id,
      UInt32 cache_block_size):
   DramPerfModel(core_id, cache_block_size),
   m_queue_model(NULL),
   m_dram_bandwidth(8 * Sim()->getCfg()->getFloat("perf_model/dram/per_controller_bandwidth")), // Convert bytes to bits
   m_total_queueing_delay(SubsecondTime::Zero()),
   m_total_access_latency(SubsecondTime::Zero())
{
   // Memory config is needed to know the amount of memory banks.
   read_memory_config(core_id);


   m_dram_access_cost = SubsecondTime::FS() * static_cast<uint64_t>(TimeConverter<float>::NStoFS(Sim()->getCfg()->getFloat("perf_model/dram/latency"))); // Operate in fs for higher precision before converting to uint64_t/SubsecondTime

   // Read the low power access cost.
   m_dram_access_cost_lowpower  = SubsecondTime::FS() * static_cast<uint64_t>(TimeConverter<float>::NStoFS(Sim()->getCfg()->getFloat("perf_model/dram/variable/latency_lowpower"))); // Operate in fs for higher precision before converting to uint64_t/SubsecondTime

   if (Sim()->getCfg()->getBool("perf_model/dram/queue_model/enabled"))
   {
      m_queue_model = QueueModel::create("dram-queue", core_id, Sim()->getCfg()->getString("perf_model/dram/queue_model/type"),
                                         m_dram_bandwidth.getRoundedLatency(8 * cache_block_size)); // bytes to bits
   }

   registerStatsMetric("dram", core_id, "total-access-latency", &m_total_access_latency);
   registerStatsMetric("dram", core_id, "total-queueing-delay", &m_total_queueing_delay);
}

DramPerfModelVariable::~DramPerfModelVariable()
{
   if (m_queue_model)
   {
     delete m_queue_model;
      m_queue_model = NULL;
   }
}

SubsecondTime
DramPerfModelVariable::getAccessLatency(SubsecondTime pkt_time, UInt64 pkt_size, core_id_t requester, IntPtr address, DramCntlrInterface::access_t access_type, ShmemPerf *perf)
{

   // pkt_size is in 'Bytes'
   // m_dram_bandwidth is in 'Bits per clock cycle'
   if ((!m_enabled) ||
         (requester >= (core_id_t) Config::getSingleton()->getApplicationCores()))
   {
      return SubsecondTime::Zero();
   }


   SubsecondTime processing_time = m_dram_bandwidth.getRoundedLatency(8 * pkt_size); // bytes to bits

   // Compute Queue Delay
   SubsecondTime queue_delay;
   if (m_queue_model)
   {
      queue_delay = m_queue_model->computeQueueDelay(pkt_time, processing_time, requester);
   }
   else
   {
      queue_delay = SubsecondTime::Zero();
   }

   // Get the memory bank corresponding to the address.
   UInt32 bank_nr = get_address_bank(address, requester);


   int bank_mode = Sim()->m_bank_mode_map[bank_nr];

   SubsecondTime access_latency;

   // Distinguish between dram power modes.
   if (bank_mode == 0) // Low power mode
   {
      access_latency = queue_delay + processing_time + m_dram_access_cost_lowpower;
   }
   else
   {
      access_latency = queue_delay + processing_time + m_dram_access_cost;
   }

   perf->updateTime(pkt_time);
   perf->updateTime(pkt_time + queue_delay, ShmemPerf::DRAM_QUEUE);
   perf->updateTime(pkt_time + queue_delay + processing_time, ShmemPerf::DRAM_BUS);
   perf->updateTime(pkt_time + access_latency, ShmemPerf::DRAM_DEVICE);

   m_num_accesses ++;
   m_total_access_latency += access_latency;
   m_total_queueing_delay += queue_delay;

   return access_latency;
}


void 
DramPerfModelVariable::read_memory_config(core_id_t requester)
{
   cout << "[dram-perfmodel_variable] reading memory config\n";
   TYPE_OF_STACK = Sim()->getCfg()->getStringArray("memory/type_of_stack", requester);
   NUM_OF_CHANNELS = Sim()->getCfg()->getInt("memory/num_channels");
   aNUM_OF_BANKS = Sim()->getCfg()->getInt("memory/num_banks");
   //BANK_ADDRESS_BITS = Sim()->getCfg()->getInt("memory/num_bank_address_bits");
   BANK_ADDRESS_BITS = log2(aNUM_OF_BANKS);
   BANK_OFFSET_IN_PA = Sim()->getCfg()->getInt("memory/bank_offset_in_pa");
   //BANKS_PER_LAYER = Sim()->getCfg()->getInt("memory/banks_per_layer");
   if (TYPE_OF_STACK == "DDR")
      BANKS_PER_LAYER = aNUM_OF_BANKS;
   else
      BANKS_PER_LAYER = NUM_OF_CHANNELS;

   //BANKS_PER_CHANNEL = Sim()->getCfg()->getInt("memory/banks_per_channel");
   BANKS_PER_CHANNEL = (aNUM_OF_BANKS/NUM_OF_CHANNELS) - 1;
   BANK_MASK = (((1<<(BANK_ADDRESS_BITS))-1) << BANK_OFFSET_IN_PA);

}


UInt32
DramPerfModelVariable::get_address_bank(IntPtr address, core_id_t requester)
{
    SInt32 memory_controllers_interleaving = 0;
    memory_controllers_interleaving = Sim()->getCfg()->getInt("perf_model/dram/controllers_interleaving");

    UInt32 bank = -1;

   if(TYPE_OF_STACK ==  "3Dmem" || TYPE_OF_STACK == "2.5D") {
      if(ENABLE_CHANNEL_PARTITIONING)
            bank = (((address & BANK_MASK) >> BANK_OFFSET_IN_PA) & BANKS_PER_CHANNEL) * BANKS_PER_LAYER + (requester/memory_controllers_interleaving);
      else {
            bank = (((address & BANK_MASK) >> BANK_OFFSET_IN_PA) & BANKS_PER_CHANNEL) * BANKS_PER_LAYER + MCP_FLAG % NUM_OF_CHANNELS;
            MCP_FLAG++;
            if(MCP_FLAG == NUM_OF_CHANNELS)
               MCP_FLAG = 0;
      }
   }
   else {
      if(TYPE_OF_STACK == "3D") {
            if(ENABLE_CHANNEL_PARTITIONING)
               bank = (((address & BANK_MASK) >> BANK_OFFSET_IN_PA) & BANKS_PER_CHANNEL) * BANKS_PER_LAYER + (requester/memory_controllers_interleaving);
            else {
               bank = (((address & BANK_MASK) >> BANK_OFFSET_IN_PA) & BANKS_PER_CHANNEL) * BANKS_PER_LAYER + MCP_FLAG % (NUM_OF_CHANNELS*1);
               MCP_FLAG++;
               if(MCP_FLAG == (NUM_OF_CHANNELS*1))
                  MCP_FLAG = 0;
            }
      }
      else {
            if(TYPE_OF_STACK ==  "DDR") {
               bank = ((address & BANK_MASK) >> BANK_OFFSET_IN_PA);
            }
            else {
               printf("Invalid type of stack\n");
               exit(0);
            }
      }
      
   }

   return bank;

}
