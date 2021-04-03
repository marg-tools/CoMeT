/**
 * This header implements the const. freq DVFS policy
 */

#ifndef __DVFS_CONSTFREQ_H
#define __DVFS_CONSTFREQ_H

#include <vector>
#include "dvfspolicy.h"
#include "performance_counters.h"

class DVFSConstFreq : public DVFSPolicy {
public:
    DVFSConstFreq(const PerformanceCounters *performanceCounters, int coreRows, int coreColumns, int activeCoreFreq, int idleCoreFreq);
    virtual std::vector<int> getFrequencies(const std::vector<int> &oldFrequencies, const std::vector<bool> &activeCores);

private:
    const PerformanceCounters *performanceCounters;

    unsigned int coreRows;
    unsigned int coreColumns;
    int activeCoreFreq;
    int idleCoreFreq;
};

#endif
