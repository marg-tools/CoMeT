/**
 * Header for memory DTM.
 */

#ifndef __DRAM_CUSTOM_H
#define __DRAM_CUSTOM_H

#include <map>

#include "drampolicy.h"
#include "performance_counters.h"

class DramCustom : public DramPolicy {
public:
    DramCustom(
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
