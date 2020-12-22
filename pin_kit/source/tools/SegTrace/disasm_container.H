/*
 * Copyright 2002-2019 Intel Corporation.
 * 
 * This software is provided to you as Sample Source Code as defined in the accompanying
 * End User License Agreement for the Intel(R) Software Development Products ("Agreement")
 * section 1.L.
 * 
 * This software and the related documents are provided as is, with no express or implied
 * warranties, other than those that are expressly stated in the License.
 */

#include <string>
#include <map>


/*!
 * A container which holds an instruction disassembly for a sparse collection of
 * interesting instructions.
 */
class DISASM_CONTAINER
{
  public:
    DISASM_CONTAINER()
    {
        PIN_InitLock(&_lock);
    }

    VOID Add(ADDRINT addr, const std::string &dis)
    {
        PIN_GetLock(&_lock, 1);
        _map[addr] = dis;
        PIN_ReleaseLock(&_lock);
    }

    std::string Get(ADDRINT addr)
    {
        PIN_GetLock(&_lock, 1);
        MAP::iterator it = _map.find(addr);
        if (it == _map.end())
        {
            PIN_ReleaseLock(&_lock);
            return "";
        }

        std::string dis = (*it).second;
        PIN_ReleaseLock(&_lock);
        return dis;
    }

  private:
    PIN_LOCK _lock;

    typedef std::map<ADDRINT, std::string> MAP;
    MAP _map;
};

