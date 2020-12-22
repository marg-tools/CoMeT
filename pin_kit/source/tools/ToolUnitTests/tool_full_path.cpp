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

/*! @file
 *  This Pin tool prints full name of the tool DLL file
 *  using Pin client API PIN_ToolFullPath().
 *  The printed name used as pattern of grep in test
 *  to validate correctness of value returned by the API.
 */

#include "pin.H"
#include <iostream>
using std::cerr;
using std::flush;

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char *argv[])
{
    PIN_InitSymbols();

    if (PIN_Init(argc,argv))
    {
        return 1;
    }

    const char * toolName = PIN_ToolFullPath();
    cerr << toolName << flush;

    // Never returns
    PIN_StartProgram();
    
    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
