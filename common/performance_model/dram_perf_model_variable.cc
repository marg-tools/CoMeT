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
   // TODO added by Leo to keep track of memory banks
   read_memory_config(core_id); // also added by leo

   for (int i = 0; i < aNUM_OF_BANKS; i++)
   {
      m_bank_status_map[i] = 1; // all banks are on
   }


   m_dram_access_cost = SubsecondTime::FS() * static_cast<uint64_t>(TimeConverter<float>::NStoFS(Sim()->getCfg()->getFloat("perf_model/dram/variable/latency_normal"))); // Operate in fs for higher precision before converting to uint64_t/SubsecondTime

   // added by leo
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



   //get the memory bank corresponding to the address
   UInt32 bank_nr = get_address_bank(address, requester);
   // cout << "getting the access latency for bank " << bank << "\n";

   // LEO get the status for this bank
   int bank_status = m_bank_status_map[bank_nr];

   SubsecondTime access_latency;

   if (bank_status == 0) // LEO if the bank is in low_power mode
   {
      access_latency = queue_delay + processing_time + m_dram_access_cost_lowpower;
   }
   else
   {
      access_latency = queue_delay + processing_time + m_dram_access_cost;
      
   }
   cout << "bank " << bank_nr << " status is " << bank_status << ".\t Access latency is " << access_latency << "\n";



   // Leo: want to make a distinction here between high and low power mode
   // SubsecondTime access_latency = queue_delay + processing_time + m_dram_access_cost; //


   perf->updateTime(pkt_time);
   perf->updateTime(pkt_time + queue_delay, ShmemPerf::DRAM_QUEUE);
   perf->updateTime(pkt_time + queue_delay + processing_time, ShmemPerf::DRAM_BUS);
   perf->updateTime(pkt_time + access_latency, ShmemPerf::DRAM_DEVICE);

   // Update Memory Counters
   m_num_accesses ++;
   m_total_access_latency += access_latency;
   m_total_queueing_delay += queue_delay;
   // cout << "from the cfg           " << Sim()->getCfg()->getFloat("perf_model/dram/variable/latency_normal") << "\n";
   // cout << "from the cfg converted " << TimeConverter<float>::NStoFS(Sim()->getCfg()->getFloat("perf_model/dram/variable/latency_normal")) << "\n";
   // cout << "lowpower from the cfg           " << Sim()->getCfg()->getFloat("perf_model/dram/variable/latency_lowpower") << "\n";
   // cout << "lowpower from the cfg converted " << TimeConverter<float>::NStoFS(Sim()->getCfg()->getFloat("perf_model/dram/variable/latency_lowpower")) << "\n";

   // cout << "using variable dram perf model\n";
   // cout << "dram access cost is " << m_dram_access_cost << "\n";
   // cout << "access latency is " << access_latency << "\n-----\n";
   // cout << "BANKS STATUS for " << aNUM_OF_BANKS << "banks\n";

   // // for (UInt8 i = 0; i < aNUM_OF_BANKS; i++){
   // //    UInt8 status = m_bank_status_map[i];
   // //    cout << m_bank_status_map[i] << ", ";
   // // }
   // // cout << "\n";

   // for (auto& x: m_bank_status_map) {
   //    std::cout << x.first << ": " << x.second << std::endl;
   // }
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

   cout << "num of channels " << NUM_OF_CHANNELS << "\n";
   cout << "num of banks " << aNUM_OF_BANKS << "\n";
   cout << "bank access bits" << BANK_ADDRESS_BITS << "\n";
   cout << "bank offset in PA" << BANK_OFFSET_IN_PA << "\n";
   cout << "banks per layer" << BANKS_PER_LAYER << "\n";
   cout << "banks per channel" << BANKS_PER_CHANNEL << "\n";
   cout << "bank mask" << BANK_MASK << "\n";
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
