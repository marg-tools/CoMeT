#include "dram_cntlr.h"
#include "dram_trace_collect.h"
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

unsigned long num_of_dram_reads;
unsigned long num_of_dram_writes;

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
    #define ACCUMULATION_TIME     (1000)    // Till 200 us bank counts will be accumalated
    #define BANK_MASK             ( ( ( 1<<(BANK_ADDRESS_BITS) ) - 1) << BANK_OFFSET_IN_PA) // Bank Address starts bank_offset bits from LSB

    // Global variables are initialized to 0 by default

    UInt64 read_access_count_per_bank[NUM_OF_BANKS];
    UInt64 read_access_count_export[NUM_OF_BANKS];
    UInt32 read_access_count = 0;
    UInt64 read_interval_start_time;
    UInt32 read_bank_accessed;
    UInt32 read_last_printed_timestamp= 0;

    UInt64 write_access_count_per_bank[NUM_OF_BANKS];
    UInt64 write_access_count_export[NUM_OF_BANKS];
    UInt32 write_access_count = 0;
    UInt64 write_interval_start_time;
    UInt32 write_bank_accessed;
    UInt32 write_last_printed_timestamp= 0;

    UInt32 total_access_count = 0;
    uintptr_t address_ptr;
    
    int on_entry_to_roi_read=0;
    int on_entry_to_roi_write=0;
    UInt64 roi_start_time_read=0;
    UInt64 roi_start_time_write=0;

    struct read_trace_data rdt[2000];
    struct write_trace_data wrt[2000];
    UInt64 read_adv_count = 0;
    UInt64 write_adv_count = 0;

      
    
#endif

#define ENABLE_CHANNEL_PARTITIONING 1
#define NUM_OF_CHANNELS 16

UInt32 MCP_FLAG;

//#define CALL_TRACE 0

void 
dram_read_trace(IntPtr address, core_id_t requester, SubsecondTime now, UInt64 m_reads)
{

   address_ptr = address;

   SInt32 memory_controllers_interleaving = 0;
   memory_controllers_interleaving = Sim()->getCfg()->getInt("perf_model/dram/controllers_interleaving");

   if(Sim()->getMagicServer()->inROI())
   {
        
     if(on_entry_to_roi_read==0)
     {
        on_entry_to_roi_read=1;
        roi_start_time_read = now.getUS();
        read_last_printed_timestamp = roi_start_time_read;
     }
     num_of_dram_reads++;
  
     #ifdef BANK_COUNTERS
        UInt32 i = 0;
        if(total_access_count==0){
           registerStatsMetric("dram", 0 , "myreads", &m_reads);
         for(i = 0; i < NUM_OF_BANKS; i = i + 1){
              read_access_count_per_bank[i]=0;
         }
        }

        ++total_access_count;
        
        //read_bank_accessed = (((address & BANK_MASK) >> BANK_OFFSET_IN_PA) & HMC_LAYER_MASK) * BANKS_PER_LAYER + (requester/memory_controllers_interleaving);
        
        if(ENABLE_CHANNEL_PARTITIONING)
            read_bank_accessed = (((address & BANK_MASK) >> BANK_OFFSET_IN_PA) & HMC_LAYER_MASK) * BANKS_PER_LAYER + (requester/memory_controllers_interleaving);
        else {
            read_bank_accessed = (((address & BANK_MASK) >> BANK_OFFSET_IN_PA) & HMC_LAYER_MASK) * BANKS_PER_LAYER + MCP_FLAG % NUM_OF_CHANNELS;
            MCP_FLAG++;
            if(MCP_FLAG == NUM_OF_CHANNELS)
                MCP_FLAG = 0;
        }

        //printf("\nRead banked accessed %d\n", read_bank_accessed) ;

        UInt64 current_time = now.getUS();
        //printf("Current time is %lu\n", current_time);
        
        
        if (current_time > ACCUMULATION_TIME + read_interval_start_time){
            read_interval_start_time = current_time - (current_time % ACCUMULATION_TIME);
            while(read_last_printed_timestamp + ACCUMULATION_TIME < read_interval_start_time){
                rdt[read_adv_count].rd_interval_start_time = read_last_printed_timestamp + ACCUMULATION_TIME;
                rdt[read_adv_count].read_access_count_per_epoch = 0;
                for(UInt32 i = 0; i < NUM_OF_BANKS; i = i + 1 ){
                    rdt[read_adv_count].bank_read_access_count[i] = 0;
                }
                ++read_adv_count;
                read_last_printed_timestamp =  read_last_printed_timestamp + ACCUMULATION_TIME;
            }

            rdt[read_adv_count].rd_interval_start_time = read_interval_start_time;
            rdt[read_adv_count].read_access_count_per_epoch = read_access_count;
            //printf("\nRead:");
            for(UInt32 i = 0; i < NUM_OF_BANKS; i = i + 1 ){
                //printf("%d,", read_access_count_per_bank[i]);
                rdt[read_adv_count].bank_read_access_count[i] = read_access_count_per_bank[i];
                read_access_count_export[i] = read_access_count_per_bank[i];
                read_access_count_per_bank[i]=0;
              }
            ++read_adv_count;
            read_access_count=0;
            read_last_printed_timestamp = read_interval_start_time;
        }
        else {
          ++read_access_count_per_bank[read_bank_accessed];
          ++read_access_count;
        }
      
     #endif
    }
}

void
dram_write_trace(IntPtr address, core_id_t requester, SubsecondTime now, UInt64 m_writes)
{
   address_ptr = address;
   
   SInt32 memory_controllers_interleaving = 0;
   memory_controllers_interleaving = Sim()->getCfg()->getInt("perf_model/dram/controllers_interleaving");

   if(Sim()->getMagicServer()->inROI())
   {

    if(on_entry_to_roi_write==0)
     {
        on_entry_to_roi_write=1;
        roi_start_time_write = now.getUS();
        write_last_printed_timestamp = roi_start_time_write;
     }
     num_of_dram_writes++;
  
     #ifdef DEBUG
     static int access_count = 1;
     printf("Dir. MSI: Write Access Count = %d\n",access_count++);
     #endif


     #ifdef BANK_COUNTERS
        UInt32 i = 0;
        if(total_access_count==0){
            registerStatsMetric("dram", 0 , "mywrites", &m_writes);
            for(i = 0; i < NUM_OF_BANKS; i = i + 1){
                write_access_count_per_bank[i]=0;
            }
        }

        ++total_access_count;
        
        //write_bank_accessed = (((address & BANK_MASK) >> BANK_OFFSET_IN_PA) & HMC_LAYER_MASK) * BANKS_PER_LAYER + (requester/memory_controllers_interleaving);

        if(ENABLE_CHANNEL_PARTITIONING)
            write_bank_accessed = (((address & BANK_MASK) >> BANK_OFFSET_IN_PA) & HMC_LAYER_MASK) * BANKS_PER_LAYER + (requester/memory_controllers_interleaving);
        else {
            write_bank_accessed = (((address & BANK_MASK) >> BANK_OFFSET_IN_PA) & HMC_LAYER_MASK) * BANKS_PER_LAYER + MCP_FLAG % NUM_OF_CHANNELS;
            MCP_FLAG++;
            if(MCP_FLAG == NUM_OF_CHANNELS)
                MCP_FLAG = 0;
        }
        
        //printf("\nWrite banked accessed %d\n", write_bank_accessed) ;
        UInt64 current_time = now.getUS();
        //printf("Current time is put()%u\n", current_time);
        
        
        if (current_time > ACCUMULATION_TIME + write_interval_start_time){
            write_interval_start_time = current_time - (current_time % ACCUMULATION_TIME);
            while(write_last_printed_timestamp + ACCUMULATION_TIME < write_interval_start_time){
                wrt[write_adv_count].wr_interval_start_time = write_last_printed_timestamp + ACCUMULATION_TIME;
                wrt[write_adv_count].write_access_count_per_epoch = 0;
                for(UInt32 i = 0; i < NUM_OF_BANKS; i = i + 1 ){
                    wrt[read_adv_count].bank_write_access_count[i] = 0;
                }
                ++write_adv_count;
                write_last_printed_timestamp =  write_last_printed_timestamp + ACCUMULATION_TIME;
            }

            wrt[write_adv_count].wr_interval_start_time = write_interval_start_time;
            wrt[write_adv_count].write_access_count_per_epoch = write_access_count;
            //printf("\nWrite:");
            for(UInt32 i = 0; i < NUM_OF_BANKS; i = i + 1 ){
                //printf("%d,", write_access_count_per_bank[i]);
                wrt[write_adv_count].bank_write_access_count[i] = write_access_count_per_bank[i];
                write_access_count_export[i] = write_access_count_per_bank[i];
                write_access_count_per_bank[i]=0;
              }
            ++write_adv_count;
            write_access_count=0;
            write_last_printed_timestamp = write_interval_start_time;
        }
        else {
          ++write_access_count_per_bank[write_bank_accessed];
          ++write_access_count;
        }
        
     #endif
    }
}

