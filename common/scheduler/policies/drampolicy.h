/**
 * This header implements the DRAM interface.
 * A mapping policy is responsible for DVFS scaling.
 * 
 * TODO MADE BY LEO
 */

#ifndef __DRAMPOLICY_H
#define __DRAMPOLICY_H

#include "simulator.h" // to get access to the m_bank_status_map
#include <map>

class DramPolicy {
public:
    virtual ~DramPolicy() {}
    virtual std::map<int, int> getMemStatus() = 0;
};

#endif