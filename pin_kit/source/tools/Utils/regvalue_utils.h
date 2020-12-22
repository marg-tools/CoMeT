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

#ifndef REGVALUE_UTILS_H
#define REGVALUE_UTILS_H


/////////////////////
// INCLUDES
/////////////////////

#include <string>
#include <ostream>
#include "pin.H"

using std::string;
using std::ostream;


/////////////////////
// GLOBAL VARIABLES
/////////////////////

// Booleans indicating the supported ISA extensions.
extern const bool hasAvxSupport;
extern const bool hasAvx512fSupport;


/////////////////////
// FUNCTION DECLARATIONS
/////////////////////

// Returns a string of the hex representation of the given "value" of length "size" bytes.
string Val2Str(const void* value, unsigned int size);

// Compare two values of length "size" bytes.
bool CompareValues(const void* value, const void* expected, unsigned int size, ostream& ost);

// Assign a PIN_REGISTER object with a new value.
void AssignNewPinRegisterValue(PIN_REGISTER* pinreg, const UINT64* newval, UINT qwords);

#endif // REGVALUE_UTILS_H
