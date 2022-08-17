/**
 * This header implements the DRAM policy interface.
 */

#ifndef __DRAMPOLICY_H
#define __DRAMPOLICY_H

#include <map>

#define LOW_POWER 0
#define NORMAL_POWER 1

class DramPolicy {
public:
    virtual ~DramPolicy() {}
    virtual std::map<int, int> getNewBankModes(std::map<int, int> old_bank_modes) = 0;
};

#endif