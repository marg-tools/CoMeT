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
 * This test tool verifies that Pin correctly handles the jcx instruction with the 
   addr16 prefix
 */

#include "pin.H"


VOID VerifyNotTaken(BOOL taken)
{
    if (taken)
    {
        printf ("taken\n");
    }
    else
    {
        printf ("notTaken\n");
    }
    fflush(stdout);
}

/*!
 * Instruction instrumentation routine.
 */
VOID Instruction(INS ins, VOID* v)
{
    if (INS_Opcode(ins)==XED_ICLASS_JRCXZ)
    {
        INS_InsertCall(ins,
                       IPOINT_BEFORE,
                       AFUNPTR(VerifyNotTaken),
                       IARG_BRANCH_TAKEN,
                       IARG_END);
    }
}

/*!
 * The main procedure of the tool.
 */
int main(int argc, char * argv[])
{
    PIN_Init(argc, argv);
    INS_AddInstrumentFunction(Instruction, 0);
    PIN_StartProgram();    // Never returns
    return 0;
}
