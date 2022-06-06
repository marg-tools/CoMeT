/**
 * This header implements the DRAM policy interface.
 * TODO LEO
 */

#ifndef __DRAMPOLICY_H
#define __DRAMPOLICY_H

#include "simulator.h" // to get access to the m_bank_mode_map
#include <map>

class DramPolicy {
public:
    virtual ~DramPolicy() {}
    virtual std::map<int, int> getNewBankModes() = 0;
};

#endif