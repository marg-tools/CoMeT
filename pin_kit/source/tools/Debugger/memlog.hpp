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

#ifndef MEMLOG_HPP
#define MEMLOG_HPP

#include <map>


class MEMLOG
{
public:
    void Record(ADDRINT addr, ADDRINT size)
    {
        UINT8 *ptr = reinterpret_cast<UINT8 *>(addr);

        for (ADDRINT i = 0;  i < size;  i++)
        {
            // Only inserts 'val' if address not yet in _bytes.
            //
            _bytes.insert(std::make_pair(addr+i, ptr[i]));
        }
    }

    void Restore()
    {
        for (BYTE_MAP::iterator it = _bytes.begin();  it != _bytes.end();  ++it)
        {
            UINT8 *ptr = reinterpret_cast<UINT8 *>(it->first);
            *ptr = it->second;
        }
        _bytes.clear();
    }

private:
    typedef std::map<ADDRINT, UINT8> BYTE_MAP;
    BYTE_MAP _bytes;
};

#endif // file guard
