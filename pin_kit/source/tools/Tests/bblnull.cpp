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

#include <stdio.h>
#include "pin.H"

/* @file
 * Instrument every basic block with an empty analysis routine.
 * Use for timing measurements of bare instrumentation overhead.
 */

VOID BblRef()
{
    // nada
}
    
VOID Instruction(INS ins, VOID *v)
{
    if (INS_IsControlFlow(ins) || !INS_Valid(INS_Next(ins)))
    {
        INS_InsertCall(
            ins, IPOINT_BEFORE, (AFUNPTR)BblRef,
            IARG_END);
    }
}

int main(INT32 argc, CHAR **argv)
{
    PIN_Init(argc, argv);
    INS_AddInstrumentFunction(Instruction, 0);
    
    // Never returns
    PIN_StartProgram();
    
    return 0;
}
