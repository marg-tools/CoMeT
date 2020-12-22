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
 *  check the RTN_NumIns interface.
 */

#include "pin_tests_util.H"

VOID Rtn(RTN rtn, VOID * v)
{
    RTN_Open(rtn);
    UINT32 insNum2 = 0;
    RTN_Close(rtn);// The rtn is intentionally closed and then it is opened again.
                   // This is done in order to check the correctness of both
                   // "RTN_NumIns" and "RTN_InsTail" independently.
                
    UINT32 insNum1 = RTN_NumIns(rtn);
    RTN_Open(rtn);
    for (INS ins = RTN_InsTail(rtn); INS_Valid(ins); ins = INS_Prev(ins)) {
        insNum2++;
    }
    TEST(insNum1 == insNum2, "RTN_NumIns failed");
    RTN_Close(rtn);
}

int main(INT32 argc, CHAR **argv)
{
    PIN_Init(argc, argv);
    
    RTN_AddInstrumentFunction(Rtn, 0);
    
    // Never returns
    PIN_StartProgram();
    
    return 0;
}
