#ifndef __DRAM_PERF_MODEL_LOWPOWER_H__
#define __DRAM_PERF_MODEL_LOWPOWER_H__

#include "dram_perf_model.h"
#include "queue_model.h"
#include "fixed_types.h"
#include "subsecond_time.h"
#include "dram_cntlr_interface.h"

#include "math.h"
#include <unordered_map>
#include <map>

class DramPerfModelLowpower : public DramPerfModel
{
   private:
      QueueModel* m_queue_model;
      SubsecondTime m_dram_access_cost;
      SubsecondTime m_dram_access_cost_lowpower;
      ComponentBandwidth m_dram_bandwidth;

      SubsecondTime m_total_queueing_delay;
      SubsecondTime m_total_access_latency;

      // TODO leo These are necessary to calculate the bank from the memory address.
      UInt64 aNUM_OF_BANKS;
      UInt64 BANK_ADDRESS_BITS;
      UInt64 BANK_OFFSET_IN_PA;
      UInt64 BANKS_PER_LAYER;
      UInt64 BANKS_PER_CHANNEL;
      UInt64 BANK_MASK;
      UInt64 NUM_OF_CHANNELS;
      String TYPE_OF_STACK;
      UInt32 MCP_FLAG;

   public:
      DramPerfModelLowpower(core_id_t core_id,
            UInt32 cache_block_size);

      ~DramPerfModelLowpower();

      SubsecondTime getAccessLatency(SubsecondTime pkt_time, UInt64 pkt_size, core_id_t requester, IntPtr address, DramCntlrInterface::access_t access_type, ShmemPerf *perf);

      void read_memory_config(core_id_t requester);
      UInt32 get_address_bank(IntPtr address, core_id_t requester);
};

#endif /* __DRAM_PERF_MODEL_LOWPOWER_H__ */
