/**
 * This header implements memory DTM using a low power mode.
 */

#ifndef __DRAM_LOWPOWER_H
#define __DRAM_LOWPOWER_H

#include <map>

#include "drampolicy.h"
#include "performance_counters.h"

class DramLowpower : public DramPolicy {
public:
    DramLowpower(
        const PerformanceCounters *performanceCounters,
        int numberOfBanks,
        float dtmCriticalTemperature,
        float dtmRecoveredTemperature);
    virtual std::map<int,int> getNewBankModes(std::map<int,int> old_bank_modes);

private:
    const PerformanceCounters *performanceCounters;

    unsigned int numberOfBanks;
    float dtmCriticalTemperature;
    float dtmRecoveredTemperature;
};

#endif
