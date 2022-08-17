#include "dramLowpower.h"
#include <iomanip>
#include <iostream>
#include <map>

using namespace std;

DramLowpower::DramLowpower(
        const PerformanceCounters *performanceCounters,
        int numberOfBanks,
        float dtmCriticalTemperature,
        float dtmRecoveredTemperature)
    : performanceCounters(performanceCounters),
      numberOfBanks(numberOfBanks),
      dtmCriticalTemperature(dtmCriticalTemperature),
      dtmRecoveredTemperature(dtmRecoveredTemperature) {

}

/*
Return the new memory modes, based on current temperatures.
*/
std::map<int,int> DramLowpower::getNewBankModes(std::map<int, int> old_bank_modes) {

    cout << "in DramLowpower::getNewBankModes\n";
    std::map<int,int> new_bank_mode_map;
    for (int i = 0; i < numberOfBanks; i++)
    {
        if (old_bank_modes[i] == LOW_POWER) // if the memory was already in low power mode
        {
            if (performanceCounters->getTemperatureOfBank(i) < dtmRecoveredTemperature) // temp dropped below recovery temperature
            {
                cout << "[Scheduler][dram-DTM]: thermal violation ended for bank " << i << endl;
                new_bank_mode_map[i] = NORMAL_POWER;
            }
            else
            {
                new_bank_mode_map[i] = LOW_POWER;
            }
        }
        else // if the memory was not in low power mode
        {
            if (performanceCounters->getTemperatureOfBank(i) > dtmCriticalTemperature) // temp is above critical temperature
            {
                cout << "[Scheduler][dram-DTM]: thermal violation detected for bank " << i << endl;
                new_bank_mode_map[i] = LOW_POWER;
            }
            else
            {
                new_bank_mode_map[i] = NORMAL_POWER;
            }

        }
        
    }
    return new_bank_mode_map;
}