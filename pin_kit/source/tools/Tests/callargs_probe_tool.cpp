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

#include "pin.H"
#include <iostream>
#include <fstream>
#include <stdlib.h>

#if defined(TARGET_MAC)
#define FUNC_PREFIX "_"
#else
#define FUNC_PREFIX
#endif

/* ===================================================================== */
/* Global Variables */
/* ===================================================================== */

std::ofstream TraceFile;



VOID BazArg(ADDRINT * arg1, ADDRINT * arg2, ADDRINT * arg3)
{
    *arg1 = 4;
    *arg2 = 5;
    *arg3 = 6;
}

/* ===================================================================== */

VOID Image(IMG img, VOID *v)
{
    RTN bazRtn = RTN_FindByName(img, FUNC_PREFIX "baz");
    if (RTN_Valid(bazRtn))
    {
        RTN_InsertCallProbed(bazRtn, IPOINT_BEFORE, AFUNPTR(BazArg), IARG_FUNCARG_ENTRYPOINT_REFERENCE, 0, IARG_FUNCARG_ENTRYPOINT_REFERENCE, 1, IARG_FUNCARG_ENTRYPOINT_REFERENCE, 2, IARG_END);
    }
}

/* ===================================================================== */

int main(int argc, char *argv[])
{
    PIN_InitSymbols();
    PIN_Init(argc, argv);

    IMG_AddInstrumentFunction(Image, 0);

    // Never returns
    PIN_StartProgramProbed();
    
    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
