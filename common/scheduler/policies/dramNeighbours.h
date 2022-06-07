/**
 * This header implements the ondemand governor with DTM.
 * The ondemand governor implementation is based on
 *     Pallipadi, Venkatesh, and Alexey Starikovskiy.
 *     "The ondemand governor."
 *     Proceedings of the Linux Symposium. Vol. 2. No. 00216. 2006.
 */

#ifndef __DRAM_NEIGHBOURS_H
#define __DRAM_NEIGHBOURS_H

#include <map>

#include "drampolicy.h"
#include "performance_counters.h"

class DramNeighbours : public DramPolicy { // TODO LEO i should change this to a NEW type of dram dtm
public:
    DramNeighbours(
        const PerformanceCounters *performanceCounters,
        int numberOfBanks,
        int banksInX,
        int banksInY,
        int banksInZ,
        float dtmCriticalTemperature,
        float dtmRecoveredTemperature);
    virtual std::map<int,int> getNewBankModes();

private:
    const PerformanceCounters *performanceCounters;

    unsigned int numberOfBanks;
    int banksInX;
    int banksInY;
    int banksInZ;
    float dtmCriticalTemperature;
    float dtmRecoveredTemperature;
};

#endif
