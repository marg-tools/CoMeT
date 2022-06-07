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
*/
std::map<int,int> DramNeighbours::getNewBankModes() {

    cout << "in DramNeighbours::getNewBankModes\n";

    std::map<int,int> new_bank_mode_map;
    for (int i = 0; i < numberOfBanks; i++) // first loop: turn all banks in low power mode that are cooled down on
    {
        if (Sim()->m_bank_mode_map[i] == 0) // if the memory was already in low power mode
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
        // all other banks are on
        new_bank_mode_map[i] = 1;
    }
    for (int i = 0; i < numberOfBanks; i++)
    {
        // second loop: turn all banks in normal power mode that are too hot to low power mode, as well ast heir neighbours
        if (Sim()->m_bank_mode_map[i] == 1) 
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