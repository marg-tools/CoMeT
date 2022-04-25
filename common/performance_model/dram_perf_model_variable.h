#ifndef __DRAM_PERF_MODEL_VARIABLE_H__
#define __DRAM_PERF_MODEL_VARIABLE_H__

#include "dram_perf_model.h"
#include "queue_model.h"
#include "fixed_types.h"
#include "subsecond_time.h"
#include "dram_cntlr_interface.h"

class DramPerfModelVariable : public DramPerfModel
{
   private:
      QueueModel* m_queue_model;
      SubsecondTime m_dram_access_cost;
      ComponentBandwidth m_dram_bandwidth;

      SubsecondTime m_total_queueing_delay;
      SubsecondTime m_total_access_latency;

   public:
      DramPerfModelVariable(core_id_t core_id,
            UInt32 cache_block_size);

      ~DramPerfModelVariable();

      SubsecondTime getAccessLatency(SubsecondTime pkt_time, UInt64 pkt_size, core_id_t requester, IntPtr address, DramCntlrInterface::access_t access_type, ShmemPerf *perf);
};

#endif /* __DRAM_PERF_MODEL_VARIABLE_H__ */
