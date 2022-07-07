#include "dramNeighbours.h"
#include <iomanip>
#include <iostream>
#include <map>

using namespace std;

DramNeighbours::DramNeighbours(
        const PerformanceCounters *performanceCounters,
        int numberOfBanks,
        int banksInX,
        int banksInY,
        int banksInZ,
        float dtmCriticalTemperature,
        float dtmRecoveredTemperature)
    : performanceCounters(performanceCounters),
      numberOfBanks(numberOfBanks),
      banksInX(banksInX),
      banksInY(banksInY),
      banksInZ(banksInZ),
      dtmCriticalTemperature(dtmCriticalTemperature),
      dtmRecoveredTemperature(dtmRecoveredTemperature) {

}

/*
Return the new memory modes, based on current temperatures.
Hot banks will be turned to low power mode, as well as their neighbours. Banks will recover when their temp
falls below the threshold, unless their neighbour is still hot. 
*/
std::map<int,int> DramNeighbours::getNewBankModes(std::map<int,int> old_bank_modes) {

    cout << "in DramNeighbours::getNewBankModes\n";

    std::map<int,int> new_bank_mode_map;

    // First loop: low power mode banks that cooled enough are turned back on.
    // This means that cool banks with hot neighbours will be turned on, but this will be corrected in the next loop.
    for (int i = 0; i < numberOfBanks; i++)
    {
        if (old_bank_modes[i] == 0) // if the memory is in low power mode
        {
            if (performanceCounters->getTemperatureOfBank(i) < dtmRecoveredTemperature) // temp dropped below recovery temperature
            {
                cout << "[Scheduler][dram-DTM]: thermal violation ended for bank " << i << endl;
                new_bank_mode_map[i] = 1;
            }
            else
            {
                new_bank_mode_map[i] = 0;
            }

        }
        else
        {
            new_bank_mode_map[i] = old_bank_modes[i];
        }
    }
    // Second loop: Hot banks from normal power to low power mode, as well as their neighbours.
    // and banks that are between the critical and recovery temperature, while also in low power mode, will turn their neighbours off again.
    for (int i = 0; i < numberOfBanks; i++)
    {
        if (old_bank_modes[i] == 1) 
        {
            if (performanceCounters->getTemperatureOfBank(i) > dtmCriticalTemperature) // temp is above critical temperature
            {
                cout << "[Scheduler][dram-DTM]: thermal violation detected for bank " << i << endl;
                new_bank_mode_map[i] = 0;

                // turn all neighbours off
                if (i % banksInX < banksInX - 1 && i+ 1 < numberOfBanks)
                {
                    new_bank_mode_map[i + 1] = 0;
                }
                if (i % banksInX > 0)
                {
                    new_bank_mode_map[i - 1] = 0;
                }
                if ((i + banksInX) / (banksInX * banksInY) == i / (banksInX * banksInY) && (i + banksInX) < numberOfBanks)
                {
                    new_bank_mode_map[i + banksInX] = 0;
                }
                if ((i - banksInX) / (banksInX * banksInY) == i / (banksInX * banksInY))
                {
                    new_bank_mode_map[i - banksInX] = 0;
                }
                if (i + (banksInX * banksInY) < numberOfBanks)
                {
                    new_bank_mode_map[i + (banksInX * banksInY)] = 0;
                }
                if (i - (banksInX * banksInY) > -1)
                {
                    new_bank_mode_map[i - (banksInX * banksInY)] = 0;
                }

            }

        }
    }

    return new_bank_mode_map;
}