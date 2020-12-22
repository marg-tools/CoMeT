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
 *  Check consistency of fall through in BBLs and INSes.
 */

#include "pin_tests_util.H"


VOID Trace(TRACE trace, VOID *v)
{
    for (BBL bbl = TRACE_BblTail(trace); BBL_Valid(bbl); bbl = BBL_Next(bbl)) {
        if (BBL_HasFallThrough(bbl)) {
            INS ins = BBL_InsTail(bbl);
            TEST(INS_HasFallThrough(ins), "BBL_HasFallThrough or INS_HasFallThrough failed");
        }
    }
}

int main(INT32 argc, CHAR **argv)
{
    PIN_Init(argc, argv);

    TRACE_AddInstrumentFunction(Trace, 0);

    // Never returns
    PIN_StartProgram();

    return 0;
}

