/*
 * Copyright 2002-2019 Intel Corporation.
 * 
 * This software and the related documents are Intel copyrighted materials, and your
 * use of them is governed by the express license under which they were provided to
 * you ("License"). Unless the License provides otherwise, you may not use, modify,
 * copy, publish, distribute, disclose or transmit this software or the related
 * documents without Intel's prior written permission.
 * 
 * This software and the related documents are provided as is, with no express or
 * implied warranties, other than those that are expressly stated in the License.
 */

/*! @file
 *  This file contains utility routines for cache/memory PIN tools
 */

#ifndef PIN_UTIL_H
#define PIN_UTIL_H

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>

#define KILO 1024
#define MEGA (KILO*KILO)
#define GIGA (KILO*MEGA)

GLOBALFUN std::string StringInt(UINT64 val, UINT32 width=0, CHAR padding=' ')
{
    std::ostringstream ostr;
    ostr.setf(std::ios::fixed,std::ios::floatfield);
    ostr.fill(padding);
    ostr << std::setw(width) << val;
    return ostr.str();
}

GLOBALFUN std::string StringHex(UINT64 val, UINT32 width=0, CHAR padding=' ')
{
    std::ostringstream ostr;
    ostr.setf(std::ios::fixed,std::ios::floatfield);
    ostr.fill(padding);
    ostr << std::setw(width) << std::hex << "0x" << val;
    return ostr.str();
}

GLOBALFUN std::string StringString(std::string val, UINT32 width=0, CHAR padding=' ')
{
    std::ostringstream ostr;
    ostr.setf(std::ios::fixed,std::ios::floatfield);
    ostr.fill(padding);
    ostr << std::setw(width) << val;
    return ostr.str();
}

#endif // PIN_UTIL_H
