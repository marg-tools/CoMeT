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

#include <cassert>
#include <string>
#include <cstring>
#include <sstream>
#include "regvalue_utils.h"

using std::endl;
using std::flush;
using std::string;
using std::stringstream;
using std::hex;


/////////////////////
// EXTERNAL FUNCTIONS
/////////////////////

extern "C" bool ProcessorSupportsAvx();
extern "C" bool SupportsAvx512f();


/////////////////////
// GLOBAL VARIABLES
/////////////////////

// Boolean indicating whether the system supports AVX instructions and registers.
const bool hasAvxSupport = ProcessorSupportsAvx();
const bool hasAvx512fSupport = SupportsAvx512f();


/////////////////////
// INTERNAL FUNCTIONS IMPLEMENTATION
/////////////////////

template<typename SIZETYPE>
static bool CompareSizedWord(const unsigned char * value, const unsigned char * expected, unsigned int element,
                             unsigned int totalSize, ostream& ost)
{
    if (*((SIZETYPE*)(&value[element << 3])) != *((SIZETYPE*)(&expected[element << 3])))
    {
        ost << "WARNING: Expected value: " << Val2Str((void*)expected, totalSize) << endl << flush;
        ost << "WARNING: Received value: " << Val2Str((void*)value, totalSize) << endl << flush;
        return false;
    }
    return true;
}


/////////////////////
// API FUNCTIONS IMPLEMENTATION
/////////////////////

string Val2Str(const void* value, unsigned int size)
{
    stringstream sstr;
    sstr << hex;
    const unsigned char* cval = (const unsigned char*)value;
    // Traverse cval from end to beginning since the MSB is in the last block of cval.
    while (size)
    {
        --size;
        sstr << (unsigned int)cval[size];
    }
    return string("0x")+sstr.str();
}

bool CompareValues(const void* value, const void* expected, unsigned int size, ostream& ost)
{
    if (0 != memcmp(value, expected, size))
    {
        ost << "WARNING: Expected value: " << Val2Str(expected, size) << endl << flush;
        ost << "WARNING: Received value: " << Val2Str(value, size) << endl << flush;
        return false;
    }
    return true;
}

void AssignNewPinRegisterValue(PIN_REGISTER* pinreg, const UINT64* newval, UINT qwords)
{
    static UINT maxQwords = sizeof(PIN_REGISTER) / sizeof(UINT64);
    assert(qwords <= maxQwords);
    for (UINT i = 0; i < qwords; ++i)
    {
        pinreg->qword[i] = newval[i];
    }
}
