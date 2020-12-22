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

#ifndef REGISTER_MODIFICATION_UTILS_H
#define REGISTER_MODIFICATION_UTILS_H


/////////////////////
// INCLUDES
/////////////////////

#include "regvalue_test_utils.h"


/////////////////////
// FUNCTION DECLARATIONS
/////////////////////

///// Test Logic

// The regvalue_app application stores the register values after the ChangeRegs routine completes. The tool can then
// inspect these values to check whether value replacement was successful. This function is an analysis routine for
// the SaveAppPointers() function defined in the regvalue_app application. It is used to save these pointers.
void ToolSaveAppPointers(void* gprptr, void* stptr, void* xmmptr, void* ymmptr, void* zmmptr, void* opmaskptr,
                         void* /* ostream* */ ostptr);

// Analysis routine for the SaveRegsToMem() function defined in the regvalue_app application. This routine compares the
// register values stored by the application after the ChangeRegs routine with the expected tool-assigned values defined
// in regvalues.h.
void CheckToolModifiedValues(CONTEXT * ctxt, void* /* ostream* */ ostptr);

#endif // REGISTER_MODIFICATION_UTILS_H
