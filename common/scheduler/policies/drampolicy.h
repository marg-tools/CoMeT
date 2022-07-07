/**
 * This header implements the DRAM policy interface.
 * TODO LEO
 */

#ifndef __DRAMPOLICY_H
#define __DRAMPOLICY_H

#include <map>

class DramPolicy {
public:
    virtual ~DramPolicy() {}
    virtual std::map<int, int> getNewBankModes(std::map<int, int> old_bank_modes) = 0;
};

#endif