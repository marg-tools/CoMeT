#pragma once

// Define to re-enable DramAccessCount
//#define ENABLE_DRAM_ACCESS_COUNT

#include <unordered_map>
#include <vector>
#include "dram_cntlr.h"
#include "dram_perf_model.h"
#include "shmem_msg.h"
#include "shmem_perf.h"
#include "fixed_types.h"
#include "memory_manager_base.h"
#include "dram_cntlr_interface.h"
#include "subsecond_time.h"
#include "core.h"
#include "log.h"
#include "subsecond_time.h"
#include "stats.h"
#include "fault_injection.h"
#include "shmem_perf.h"

using namespace std;
#define MAX_NUM_OF_BANKS (128)

struct read_trace_data
{
      UInt64 rd_interval_start_time = 0;
      UInt32 read_access_count_per_epoch = 0;
      UInt32 bank_read_access_count[MAX_NUM_OF_BANKS];
      UInt32 bank_read_access_count_lowpower[MAX_NUM_OF_BANKS];
};

struct write_trace_data
{
      UInt64 wr_interval_start_time = 0;
      UInt32 write_access_count_per_epoch = 0;
      UInt32 bank_write_access_count[MAX_NUM_OF_BANKS]; 
      UInt32 bank_write_access_count_lowpower[MAX_NUM_OF_BANKS];
};

void read_memory_config(core_id_t requester);
void dram_read_trace(IntPtr address, core_id_t requester, SubsecondTime now, UInt64 m_reads);
void dram_write_trace(IntPtr address, core_id_t requester, SubsecondTime now, UInt64 m_writes);
UInt32 get_address_bank(IntPtr address, core_id_t requester);