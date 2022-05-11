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

// std::vector<int> DramLowpower::getFrequencies(const std::vector<int> &oldFrequencies, const std::vector<bool> &activeCores) {
//     cout << "in DramLowpower::GetFrequences\n";
//     if (throttle()) {
//         std::vector<int> minFrequencies(numberOfCores, minFrequency);
//         cout << "[Scheduler][dram-DTM]: in throttle mode -> return min. frequencies" << endl;
//         return minFrequencies;
//     } else {
//         std::vector<int> frequencies(numberOfCores);

//         for (unsigned int coreCounter = 0; coreCounter < numberOfCores; coreCounter++) {
//             if (activeCores.at(coreCounter)) {
//                 float power = performanceCounters->getPowerOfCore(coreCounter);
//                 float temperature = performanceCounters->getTemperatureOfCore(coreCounter);
//                 int frequency = oldFrequencies.at(coreCounter);
//                 float utilization = performanceCounters->getUtilizationOfCore(coreCounter);

//                 cout << "[Scheduler][ondemand]: Core " << setw(2) << coreCounter << ":";
//                 cout << " P=" << fixed << setprecision(3) << power << " W";
//                 cout << "  f=" << frequency << " MHz";
//                 cout << "  T=" << fixed << setprecision(1) << temperature << " C";  // avoid the '°' symbol, it is not ASCII
//                 cout << "  utilization=" << fixed << setprecision(3) << utilization << endl;

//                 // use same period for upscaling and downscaling as described in "The ondemand governor."
//                 if (utilization > upThreshold) {
//                     cout << "[Scheduler][ondemand]: utilization > upThreshold";
//                     if (frequency == maxFrequency) {
//                         cout << " but already at max frequency" << endl;
//                     } else {
//                         cout << " -> go to max frequency" << endl;
//                         frequency = maxFrequency;
//                     }
//                 } else if (utilization < downThreshold) {
//                     cout << "[Scheduler][ondemand]: utilization < downThreshold";
//                     if (frequency == minFrequency) {
//                         cout << " but already at min frequency" << endl;
//                     } else {
//                         cout << " -> lower frequency" << endl;
//                         frequency = frequency * 80 / 100;
//                         frequency = (frequency / frequencyStepSize) * frequencyStepSize;  // round
//                         if (frequency < minFrequency) {
//                             frequency = minFrequency;
//                         }
//                     }
//                 }

//                 frequencies.at(coreCounter) = frequency;
//             } else {
//                 frequencies.at(coreCounter) = minFrequency;
//             }
//         }

//         return frequencies;
//     }
// }

std::map<int,int> DramLowpower::getMemStatus() {
    cout << "in DramLowpower::getMemStatus\n";
    std::map<int,int> new_bank_status_map;
    for (int i = 0; i < numberOfBanks; i++)
    {
        if (Sim()->m_bank_status_map[i] == 0) // if the memory was already in low power mode
        {
            if (performanceCounters->getTemperatureOfBank(i) < dtmRecoveredTemperature) // temp dropped below recovery temperature
            {
                cout << "[Scheduler][dram-DTM]: thermal violation ended for bank " << i << endl;
                new_bank_status_map[i] = 1;
            }
            else
            {
                new_bank_status_map[i] = 0;
            }
        }
        else // if the memory was not in low power mode
        {
            if (performanceCounters->getTemperatureOfBank(i) > dtmCriticalTemperature) // temp is above critical temperature
            {
                cout << "[Scheduler][dram-DTM]: thermal violation detected for bank " << i << endl;
                new_bank_status_map[i] = 0;
            }
            else
            {
                new_bank_status_map[i] = 1;
            }

        }
        
    }
    return new_bank_status_map;
}



//     if (performanceCounters->getPeakTemperature() > dtmCriticalTemperature) {
//         if (!in_throttle_mode) {
//             cout << "[Scheduler][ondemand-DTM]: detected thermal violation" << endl;
//         }
//         cout << "current temp" << performanceCounters->getPeakTemperature() << " > " << dtmCriticalTemperature << "\n";
//         cout << "throttling...\n";
//         in_throttle_mode = true;
//     } else if (performanceCounters->getPeakTemperature() < dtmRecoveredTemperature) {
//         if (in_throttle_mode) {
//             cout << "[Scheduler][ondemand-DTM]: thermal violation ended" << endl;
//         }
//         cout << "current temp" << performanceCounters->getPeakTemperature() << " <" << dtmRecoveredTemperature << "\n";
//         cout << "UNthrottling...\n";
//         in_throttle_mode = false;
//     }
//     return in_throttle_mode;
// }