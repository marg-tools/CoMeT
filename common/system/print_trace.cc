#include <vector>
#include "magic_server.h"
#include "sim_api.h"
#include "simulator.h"
#include "thread_manager.h"
#include "logmem.h"
#include "performance_model.h"
#include "fastforward_performance_model.h"
#include "core_manager.h"
#include "dvfs_manager.h"
#include "hooks_manager.h"
#include "stats.h"
#include "timer.h"
#include "thread.h"
#include "dram_cntlr.h"
#include "dram_trace_collect.h"

using namespace std;

extern UInt64 NUM_OF_BANKS;
extern vector<read_trace_data> rdt;
extern vector<write_trace_data> wrt;
extern UInt64 read_adv_count;
extern UInt64 write_adv_count;

void print_dram_trace()
{
	printf("\n   \tTime\t#READs\t#WRITEs\t#Access\t\tBank Counters\n");

    //printf("advance counts %lu   %lu\n", read_adv_count , write_adv_count);
    UInt64 limit;
    if(read_adv_count < write_adv_count){
        limit = read_adv_count;
        for(UInt64 i=limit; i<write_adv_count; i++){
            rdt.push_back(read_trace_data());
            rdt[i].rd_interval_start_time = wrt[i].wr_interval_start_time;
            rdt[i].read_access_count_per_epoch = 0;
            for(UInt64 j=0; j<NUM_OF_BANKS; j++){
                rdt[i].bank_read_access_count[j] = 0;
                rdt[i].bank_read_access_count_lowpower[j] = 0; // Added to keep track of low power read accesses.
            }
        }

        limit = write_adv_count;
    }
    else {
        if(read_adv_count > write_adv_count){
            limit = write_adv_count;
            for(UInt64 i=limit; i<read_adv_count; i++){
                wrt.push_back(write_trace_data());
                wrt[i].wr_interval_start_time = rdt[i].rd_interval_start_time;
                wrt[i].write_access_count_per_epoch = 0;
                for(UInt64 j=0; j<NUM_OF_BANKS; j++){
                    wrt[i].bank_write_access_count[j] = 0;
                    wrt[i].bank_write_access_count_lowpower[j] = 0; // Added to keep track of low power write accesses.
                }
            }

            limit = read_adv_count;
        }
        else {
            limit = read_adv_count;
        }
    }

    for(UInt64 i=0; i<limit; i++){
        printf("\n\n@& \t%ld\t%u\t%u\t%u\t\t",rdt[i].rd_interval_start_time,rdt[i].read_access_count_per_epoch,
        wrt[i].write_access_count_per_epoch, rdt[i].read_access_count_per_epoch+
        wrt[i].write_access_count_per_epoch);
        for(UInt64 j=0; j<NUM_OF_BANKS; j++){
            printf("%u, ", rdt[i].bank_read_access_count[j] + rdt[i].bank_read_access_count_lowpower[j] + wrt[i].bank_write_access_count[j] + wrt[i].bank_write_access_count_lowpower[j]);
        }
    }

    vector<read_trace_data>::iterator it_rd_begin, it_rd_end;
    vector<write_trace_data>::iterator it_wr_begin, it_wr_end;

    it_rd_begin = rdt.begin();
    it_rd_end = rdt.end();
    it_wr_begin = wrt.begin();
    it_wr_end = wrt.end();

    rdt.erase(it_rd_begin, it_rd_end);
    wrt.erase(it_wr_begin, it_wr_end);
    printf("\n");
}
