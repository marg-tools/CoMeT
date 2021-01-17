#include "dram_cntlr.h"
#include "memory_manager.h"
#include "core.h"
#include "log.h"
#include "subsecond_time.h"
#include "stats.h"
#include "fault_injection.h"
#include "shmem_perf.h"
#include "simulator.h"
#include "magic_server.h"
#include <stdint.h>
#include <inttypes.h>
#include "config.hpp"
#include "config.h"

unsigned long count_getdata;

unsigned long count_putdata;

#if 0
  extern Lock iolock;
#  include "simulator.h"
#  include "magic_server.h"
#  define MYLOG(...) { ScopedLock l(iolock); fflush(stdout); printf("[%s] %d%cdr %-25s@%3u: ", itostr(getShmemPerfModel()->getElapsedTime()).c_str(), getMemoryManager()->getCore()->getId(), Sim()->getCoreManager()->amiUserThread() ? '^' : '_', __FUNCTION__, __LINE__); printf(__VA_ARGS__); printf("\n"); fflush(stdout); }
#else
#  define MYLOG(...) {}
#endif

// #define DEFAULT_BANK_COUNTERS 
// #define COSKUN_DATE2012        //  Analysis and runtime management of 3D systems with stacked DRAM for boosting energy efficiency. 
// #define COSKUN_DAC2012         //  Optimizing energy efficiency of 3-D multicore systems with stacked DRAM under power and thermal constraints  
#define MY_COUNTERS               //   
    #if defined(DEFAULT_BANK_COUNTERS) || defined(COSKUN_DATE2012) || defined(COSKUN_DAC2012) || defined(MY_COUNTERS)
    #define BANK_COUNTERS
#endif

#ifdef MY_COUNTERS
    #define NUM_OF_BANKS          (128)
    #define BANK_ADDRESS_BITS     (7)
    #define BANK_OFFSET_IN_PA     (6)     // Bank Address starts bank_offset bits from LSB, least significant bits

    #define HMC_LAYER_MASK        (7)     // Layers - 1
    #define BANKS_PER_LAYER       (16) 
#endif

#ifdef COSKUN_DATE2012
    #define NUM_OF_BANKS          (16)
    #define BANK_ADDRESS_BITS     (4)     // Bit required, log(NUM_OF_BANKS)
    #define BANK_OFFSET_IN_PA     (6)     // Bank Address starts bank_offset bits from LSB, least significant bits
#endif

#ifdef DEFAULT_BANK_COUNTERS
    #define NUM_OF_BANKS          (8)
    #define BANK_ADDRESS_BITS     (3)     // Bit required, log(NUM_OF_BANKS)
    #define PHYSICAL_MEMORY_SIZE  (4096)  // 4096MB = 4GB
    #define BANK_OFFSET_IN_PA     (14)    // Bank Address starts bank_offset bits from LSB
#endif

#ifdef BANK_COUNTERS
    #define ACCUMALATION_TIME     (1000)    // Till 200 us bank counts will be accumalated
    #define PRINT_DELAY           (20)     // Every 205(=200 + 5) us print access counts for the last 200 us  
    #define PRINT_TIME_IN_PHASE2  (ACCUMALATION_TIME + PRINT_DELAY)    // Till 200 us bank counts will be accumalated
    #define PRINT_TIME_IN_PHASE1  (PRINT_DELAY)    // Till 200 us bank counts will be accumalated
    #define BANK_MASK             ( ( ( 1<<(BANK_ADDRESS_BITS) ) - 1) << BANK_OFFSET_IN_PA) // Bank Address starts bank_offset bits from LSB

    // Global variables are initialized to 0 by default
    UInt32 bank_access_counts_phase1[NUM_OF_BANKS];
    UInt32 in_phase1 = 0;
    UInt32 print_in_phase1 = 0;           // We donot want to print in the first phase
    UInt32 read_access_count_phase1 = 0;
    UInt32 write_access_count_phase1 = 0;
    UInt32 total_access_count_phase1 = 0;
    UInt32 bank_access_counts_phase2[NUM_OF_BANKS];
    UInt32 in_phase2 = 0;
    UInt32 print_in_phase2 = 1; // First print in phase2
    UInt32 read_access_count_phase2 = 0;
    UInt32 write_access_count_phase2 = 0;
    UInt32 total_access_count_phase2 = 0;
    UInt32 read_access_count = 0;
    UInt32 write_access_count = 0;
    UInt32 total_access_count = 0;
    UInt32 print_done = 0;
    UInt32 last_printed_timestamp= 0;

    UInt64 interval_start_time;
    UInt32 bank_accessed;
    uintptr_t address_ptr;

    UInt32 stats_initialized=0;
    UInt64 bank_access_counts_overall[NUM_OF_BANKS];
#endif
 
//#define CALL_TRACE 0

class TimeDistribution;

namespace PrL1PrL2DramDirectoryMSI
{

DramCntlr::DramCntlr(MemoryManagerBase* memory_manager,
      ShmemPerfModel* shmem_perf_model,
      UInt32 cache_block_size)
   : DramCntlrInterface(memory_manager, shmem_perf_model, cache_block_size)
   , m_reads(0)
   , m_writes(0)
{
   m_dram_perf_model = DramPerfModel::createDramPerfModel(
         memory_manager->getCore()->getId(),
         cache_block_size);

   m_fault_injector = Sim()->getFaultinjectionManager()
      ? Sim()->getFaultinjectionManager()->getFaultInjector(memory_manager->getCore()->getId(), MemComponent::DRAM)
      : NULL;

   m_dram_access_count = new AccessCountMap[DramCntlrInterface::NUM_ACCESS_TYPES];
   registerStatsMetric("dram", memory_manager->getCore()->getId(), "reads", &m_reads);
   registerStatsMetric("dram", memory_manager->getCore()->getId(), "writes", &m_writes);

  if (stats_initialized == 0) {
     for (int i=0; i<NUM_OF_BANKS;i++)
          registerStatsMetric("dram", i, "bank_access_counter", &bank_access_counts_overall[i]);
          stats_initialized = 1;
  }

}

DramCntlr::~DramCntlr()
{
   printDramAccessCount();
   delete [] m_dram_access_count;

   delete m_dram_perf_model;
}

boost::tuple<SubsecondTime, HitWhere::where_t>
DramCntlr::getDataFromDram(IntPtr address, core_id_t requester, Byte* data_buf, SubsecondTime now, ShmemPerf *perf)
{
   address_ptr = address;
   #ifdef CALL_TRACE
       printf("\nEntry : getDataFromDram common/core/memory_subsystem/pr_l1_pr_l2_dram_directory_msi/dram_cntlr.cc\n");
   #endif

   if (Sim()->getFaultinjectionManager())
   {
      if (m_data_map.count(address) == 0)
      {
         m_data_map[address] = new Byte[getCacheBlockSize()];
         memset((void*) m_data_map[address], 0x00, getCacheBlockSize());
      }

      // NOTE: assumes error occurs in memory. If we want to model bus errors, insert the error into data_buf instead
      if (m_fault_injector)
         m_fault_injector->preRead(address, address, getCacheBlockSize(), (Byte*)m_data_map[address], now);

      memcpy((void*) data_buf, (void*) m_data_map[address], getCacheBlockSize());
   }

   SubsecondTime dram_access_latency = runDramPerfModel(requester, now, address, READ, perf);

   ++m_reads;
   #ifdef ENABLE_DRAM_ACCESS_COUNT
   addToDramAccessCount(address, READ);
   #endif
   MYLOG("R @ %08lx latency %s", address, itostr(dram_access_latency).c_str());

   SInt32 memory_controllers_interleaving = 0;
   memory_controllers_interleaving = Sim()->getCfg()->getInt("perf_model/dram/controllers_interleaving");

   if(Sim()->getMagicServer()->inROI())
   {
    count_getdata++;

     #ifdef DEBUG
     static int access_count = 1;
     printf("Dir. MSI: Read Access Count = %d\n",access_count++);
     #endif


     #ifdef BANK_COUNTERS
        UInt32 i = 0;
        if(total_access_count==0){
           registerStatsMetric("dram", 0 , "myreads", &m_reads);
         for(i = 0; i < NUM_OF_BANKS; i = i + 1){
                    bank_access_counts_phase1[i]=0;
                    bank_access_counts_phase2[i]=0;
		    bank_access_counts_overall[i]=0;
         }
        }

        ++read_access_count;
        ++total_access_count;

        //  UInt32 bank_accessed = (address & BANK_MASK) >> BANK_OFFSET_IN_PA;
        //UInt32 bank_accessed = (((address & BANK_MASK) >> BANK_OFFSET_IN_PA) & HMC_LAYER_MASK) * BANKS_PER_LAYER + requester;
        bank_accessed = (((address & BANK_MASK) >> BANK_OFFSET_IN_PA) & HMC_LAYER_MASK) * BANKS_PER_LAYER + (requester/memory_controllers_interleaving);
        //  bank_accessed = bank_accessed & HMC_LAYER_MASK;
	//  bank_accessed = requester + bank_accessed * (16);
        //printf("requester = %d\n", requester);
        //   if( (total_access_count%200==0) || (total_access_count == 1) )
        if(total_access_count == 1)
           printf("\n   \tTime\t#READs\t#WRITEs\t#Access\tAddress\t\t#BANK\tBank Counters\n");

        UInt64 current_time = now.getUS();
        //printf("Current time is %u\n", current_time);
        UInt64 phase_time = current_time%(2 * ACCUMALATION_TIME);
        //UInt64 interval_start_time;
        // Check in which phase 1 or phase 2
        if (phase_time > ACCUMALATION_TIME){ //Accumulation time implies phase 1
           in_phase2 = 1;
           in_phase1 = 0;
           ++bank_access_counts_phase2[bank_accessed];   // During, phase2 keep on incrementing phase2 counters
           ++read_access_count_phase2;
        }
        else{
           in_phase2 = 0;
           in_phase1 = 1;
           ++bank_access_counts_phase1[bank_accessed];   // During, phase1 keep on incrementing phase1 counters
           ++read_access_count_phase1;
        }

        if (in_phase2 == 1){
           if (phase_time > PRINT_TIME_IN_PHASE2 && print_in_phase2 == 1 ){
              print_in_phase2 = 0;      // In phase 2, reset the phase 2 print flag, print phase 1 bank counters , reset them, enable phase 1 printing
              interval_start_time = current_time - current_time%(ACCUMALATION_TIME);

              while(last_printed_timestamp + ACCUMALATION_TIME < interval_start_time){
                  printf("\n@& \t%ld\t%u\t%u\t%u\t%012lx\t%u\t",(UInt64)(last_printed_timestamp + ACCUMALATION_TIME),0,0,0,(IntPtr)0,0);
                      for(UInt32 i = 0; i < NUM_OF_BANKS; i = i + 1 ){
                       //printf("%u,",0);
		       bank_access_counts_overall[i]= 0;
                  }
                  last_printed_timestamp =  last_printed_timestamp + ACCUMALATION_TIME;
              }

              total_access_count_phase1 = read_access_count_phase1 + write_access_count_phase1;
              printf("\n@& \t%ld\t%u\t%u\t%u\t%012lx\t%u\t",interval_start_time,read_access_count_phase1,write_access_count_phase1,total_access_count_phase1,address,bank_accessed);
              for(UInt32 i = 0; i < NUM_OF_BANKS; i = i + 1 ){
                 //printf("%u,",bank_access_counts_phase1[i]);
	         bank_access_counts_overall[i]= bank_access_counts_phase1[i];
                 bank_access_counts_phase1[i]=0;
              }
 	      printf("Current:%ld\n", current_time);

              read_access_count_phase1=0;
              write_access_count_phase1=0;
              print_in_phase1 = 1;      // enable phase 1 printing
              last_printed_timestamp = interval_start_time;
      	      for(UInt32 i = 0; i < NUM_OF_BANKS; i = i + 1 ){
      	        printf("%lu,",bank_access_counts_overall[i]);
      	      }
      	      printf("\n");
           }
	}
        else{
         if (phase_time > PRINT_TIME_IN_PHASE1 && print_in_phase1 == 1 ){
              print_in_phase1 = 0;      // In phase 1, reset the phase 1 print flag, print phase 2 bank counters , reset them, enable phase 2 printing
              interval_start_time = current_time - current_time%(ACCUMALATION_TIME);

              while(last_printed_timestamp + ACCUMALATION_TIME < interval_start_time){
                 printf("\n@& \t%ld\t%u\t%u\t%u\t%012lx\t%u\t",(UInt64)(last_printed_timestamp + ACCUMALATION_TIME),0,0,0,(IntPtr)0,0);
                 for(UInt32 i = 0; i < NUM_OF_BANKS; i = i + 1 ){
                       //printf("%u,",0);
		       bank_access_counts_overall[i]= 0;
                 }
                 last_printed_timestamp =  last_printed_timestamp + ACCUMALATION_TIME;
              }

              total_access_count_phase2 = read_access_count_phase2 + write_access_count_phase2;
              printf("\n@& \t%ld\t%u\t%u\t%u\t%012lx\t%u\t",interval_start_time,read_access_count_phase2,write_access_count_phase2,total_access_count_phase2,address,bank_accessed);
              for(UInt32 i = 0; i < NUM_OF_BANKS; i = i + 1 ){
                 //printf("%u,",bank_access_counts_phase2[i]);
	         bank_access_counts_overall[i]= bank_access_counts_phase2[i];
                 bank_access_counts_phase2[i]=0;
              }
 	      printf("Current:%ld\n", current_time);

              read_access_count_phase2=0;
              write_access_count_phase2=0;
              print_in_phase2 = 1;      // enable phase 2 printing
              last_printed_timestamp = interval_start_time;
      	      for(UInt32 i = 0; i < NUM_OF_BANKS; i = i + 1 ){
      	        printf("%lu,",bank_access_counts_overall[i]);
      	      }
      	      printf("\n");
           }
        }

     #endif
    }

   #ifdef CALL_TRACE
      printf("\nExit : getDataFromDram common/core/memory_subsystem/pr_l1_pr_l2_dram_directory_msi/dram_cntlr.cc");
   #endif
    
   return boost::tuple<SubsecondTime, HitWhere::where_t>(dram_access_latency, HitWhere::DRAM);
}

boost::tuple<SubsecondTime, HitWhere::where_t>
DramCntlr::putDataToDram(IntPtr address, core_id_t requester, Byte* data_buf, SubsecondTime now)
{
   address_ptr = address;
   if (Sim()->getFaultinjectionManager())
   {
      if (m_data_map[address] == NULL)
      {
         LOG_PRINT_ERROR("Data Buffer does not exist");
      }
      memcpy((void*) m_data_map[address], (void*) data_buf, getCacheBlockSize());

      // NOTE: assumes error occurs in memory. If we want to model bus errors, insert the error into data_buf instead
      if (m_fault_injector)
         m_fault_injector->postWrite(address, address, getCacheBlockSize(), (Byte*)m_data_map[address], now);
   }

   SubsecondTime dram_access_latency = runDramPerfModel(requester, now, address, WRITE, &m_dummy_shmem_perf);

   ++m_writes;
   #ifdef ENABLE_DRAM_ACCESS_COUNT
   addToDramAccessCount(address, WRITE);
   #endif
   MYLOG("W @ %08lx", address);

   SInt32 memory_controllers_interleaving = 0;
   memory_controllers_interleaving = Sim()->getCfg()->getInt("perf_model/dram/controllers_interleaving");


   if(Sim()->getMagicServer()->inROI())
   {
    count_putdata++;

     #ifdef DEBUG
     static int access_count = 1;
     printf("Dir. MSI: Write Access Count = %d\n",access_count++);
     #endif


     #ifdef BANK_COUNTERS
        UInt32 i = 0;
        if(total_access_count==0){
           registerStatsMetric("dram", 0 , "mywrites", &m_writes);
         for(i = 0; i < NUM_OF_BANKS; i = i + 1){
              bank_access_counts_phase1[i]=0;
              bank_access_counts_phase2[i]=0;
         }
        }

        ++write_access_count;
        ++total_access_count;

        //  UInt32 bank_accessed = (address & BANK_MASK) >> BANK_OFFSET_IN_PA;
        bank_accessed = (((address & BANK_MASK) >> BANK_OFFSET_IN_PA) & HMC_LAYER_MASK) * BANKS_PER_LAYER + (requester/memory_controllers_interleaving);
        //  bank_accessed = bank_accessed & HMC_LAYER_MASK;
        //  bank_accessed = requester + bank_accessed * (16);
        //printf("requester = %d\n", requester);
        //   if( (total_access_count%200==0) || (total_access_count == 1) )
        if(total_access_count == 1)
           printf("\n   \tTime\t#READs\t#WRITEs\t#Access\tAddress\t\t#BANK\tBank Counters\n");

        UInt64 current_time = now.getUS();
        //printf("Current time is %u\n", current_time);
        UInt64 phase_time = current_time%(2 * ACCUMALATION_TIME);
        //UInt64 interval_start_time;
        // Check in which phase 1 or phase 2
        if (phase_time > ACCUMALATION_TIME){ //Accumulation time implies phase 1
           in_phase2 = 1;
           in_phase1 = 0;
           ++bank_access_counts_phase2[bank_accessed];   // During, phase2 keep on incrementing phase2 counters
           ++write_access_count_phase2;
        }
        else{
           in_phase2 = 0;
           in_phase1 = 1;
           ++bank_access_counts_phase1[bank_accessed];   // During, phase1 keep on incrementing phase1 counters
           ++write_access_count_phase1;
        }
        if (in_phase2 == 1){
           if (phase_time > PRINT_TIME_IN_PHASE2 && print_in_phase2 == 1 ){
              print_in_phase2 = 0;      // In phase 2, reset the phase 2 print flag, print phase 1 bank counters , reset them, enable phase 1 printing
              interval_start_time = current_time - current_time%(ACCUMALATION_TIME);

              while(last_printed_timestamp + ACCUMALATION_TIME < interval_start_time){
                  printf("\n@& \t%ld\t%u\t%u\t%u\t%012lx\t%u\t",(UInt64)(last_printed_timestamp + ACCUMALATION_TIME),0,0,0,(IntPtr)0,0);
                  for(UInt32 i = 0; i < NUM_OF_BANKS; i = i + 1 ){
                       //printf("%u,",0);
		       bank_access_counts_overall[i]= 0;
                  }
                  last_printed_timestamp =  last_printed_timestamp + ACCUMALATION_TIME;
              }

              total_access_count_phase1 = read_access_count_phase1 + write_access_count_phase1;
              printf("\n@& \t%ld\t%u\t%u\t%u\t%012lx\t%u\t",interval_start_time,read_access_count_phase1,write_access_count_phase1,total_access_count_phase1,address,bank_accessed);
              for(UInt32 i = 0; i < NUM_OF_BANKS; i = i + 1 ){
                 //printf("%u,",bank_access_counts_phase1[i]);
	         bank_access_counts_overall[i]= bank_access_counts_phase1[i];
                 bank_access_counts_phase1[i]=0;
              }
 	      printf("Current:%ld\n", current_time);

              read_access_count_phase1=0;
              write_access_count_phase1=0;
              print_in_phase1 = 1;      // enable phase 1 printing
              last_printed_timestamp = interval_start_time;
      	      for(UInt32 i = 0; i < NUM_OF_BANKS; i = i + 1 ){
      	        printf("%lu,",bank_access_counts_overall[i]);
      	      }
      	      printf("\n");
           }
        }
        else{
           if (phase_time > PRINT_TIME_IN_PHASE1 && print_in_phase1 == 1 ){
              print_in_phase1 = 0;      // In phase 1, reset the phase 1 print flag, print phase 2 bank counters , reset them, enable phase 2 printing
              interval_start_time = current_time - current_time%(ACCUMALATION_TIME);

              while(last_printed_timestamp + ACCUMALATION_TIME < interval_start_time){
                 printf("\n@& \t%ld\t%u\t%u\t%u\t%012lx\t%u\t",(UInt64)(last_printed_timestamp + ACCUMALATION_TIME),0,0,0,(IntPtr)0,0);
                 for(UInt32 i = 0; i < NUM_OF_BANKS; i = i + 1 ){
                       //printf("%u,",0);
		       bank_access_counts_overall[i]= 0;
                 }
                 last_printed_timestamp =  last_printed_timestamp + ACCUMALATION_TIME;
              }

              total_access_count_phase2 = read_access_count_phase2 + write_access_count_phase2;
              printf("\n@& \t%ld\t%u\t%u\t%u\t%012lx\t%u\t",interval_start_time,read_access_count_phase2,write_access_count_phase2,total_access_count_phase2,address,bank_accessed);
              for(UInt32 i = 0; i < NUM_OF_BANKS; i = i + 1 ){
                 //printf("%u,",bank_access_counts_phase2[i]);
	         bank_access_counts_overall[i]= bank_access_counts_phase2[i];
                 bank_access_counts_phase2[i]=0;
              }
 	      printf("Current:%ld\n", current_time);

              read_access_count_phase2=0;
              write_access_count_phase2=0;
              print_in_phase2 = 1;      // enable phase 2 printing
              last_printed_timestamp = interval_start_time;
      	      for(UInt32 i = 0; i < NUM_OF_BANKS; i = i + 1 ){
      	        printf("%lu,",bank_access_counts_overall[i]);
      	      }
      	      printf("\n");
           }
        }

     #endif
    }

   return boost::tuple<SubsecondTime, HitWhere::where_t>(dram_access_latency, HitWhere::DRAM);
}

SubsecondTime
DramCntlr::runDramPerfModel(core_id_t requester, SubsecondTime time, IntPtr address, DramCntlrInterface::access_t access_type, ShmemPerf *perf)
{
   UInt64 pkt_size = getCacheBlockSize();
   SubsecondTime dram_access_latency = m_dram_perf_model->getAccessLatency(time, pkt_size, requester, address, access_type, perf);
   return dram_access_latency;
}

void
DramCntlr::addToDramAccessCount(IntPtr address, DramCntlrInterface::access_t access_type)
{
   m_dram_access_count[access_type][address] = m_dram_access_count[access_type][address] + 1;
}

void
DramCntlr::printDramAccessCount()
{
   for (UInt32 k = 0; k < DramCntlrInterface::NUM_ACCESS_TYPES; k++)
   {
      for (AccessCountMap::iterator i = m_dram_access_count[k].begin(); i != m_dram_access_count[k].end(); i++)
      {
         if ((*i).second > 100)
         {
            LOG_PRINT("Dram Cntlr(%i), Address(0x%x), Access Count(%llu), Access Type(%s)",
                  m_memory_manager->getCore()->getId(), (*i).first, (*i).second,
                  (k == READ)? "READ" : "WRITE");
         }
      }
   }
}

}
