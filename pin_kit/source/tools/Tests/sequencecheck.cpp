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

#include <iostream>
#include <stdio.h>
#include "pin.H"
using std::endl;

UINT64 icount = 0;
UINT64 error = 0;

// check if IARG_IP and INS_Address(ins) are coherent
VOID CheckSequence(VOID * ip, VOID * insAddr)
{
    if (ip != insAddr)
    {
        fprintf(stderr,"IP %p, insAddr %p\n", ip, insAddr);
        error++;
    }
    icount++;
#if 0    
    if ((icount % 1000) == 0)
    {
        fprintf(stderr, "%lld instructions checked\n", icount);
    }
#endif
}
    
VOID Instruction(INS ins, VOID *v)
{
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)CheckSequence, IARG_INST_PTR, IARG_ADDRINT, INS_Address(ins), IARG_END);
}

VOID Fini(INT32 code, VOID *v)
{
    std::cerr << error << " errors" << endl;
}

int main(INT32 argc, CHAR **argv)
{
    PIN_Init(argc, argv);
    INS_AddInstrumentFunction(Instruction, 0);
    PIN_AddFiniFunction(Fini, 0);
    
    // Never returns
    PIN_StartProgram();
    
    return 0;
}
