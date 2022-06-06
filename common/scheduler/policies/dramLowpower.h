/**
 * This header implements the ondemand governor with DTM.
 * The ondemand governor implementation is based on
 *     Pallipadi, Venkatesh, and Alexey Starikovskiy.
 *     "The ondemand governor."
 *     Proceedings of the Linux Symposium. Vol. 2. No. 00216. 2006.
 */

#ifndef __DRAM_LOWPOWER_H
#define __DRAM_LOWPOWER_H

#include <map>

#include "drampolicy.h"
#include "performance_counters.h"

class DramLowpower : public DramPolicy { // i should change this to a NEW type of dram dtm
public:
    DramLowpower(
        const PerformanceCounters *performanceCounters,
        int numberOfBanks,
        float dtmCriticalTemperature,
        float dtmRecoveredTemperature);
    virtual std::map<int,int> getNewBankModes();

private:
    const PerformanceCounters *performanceCounters;

    unsigned int numberOfBanks;
    float dtmCriticalTemperature;
    float dtmRecoveredTemperature;
};

#endif
