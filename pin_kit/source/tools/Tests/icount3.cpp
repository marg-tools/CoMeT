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
#include "pin.H"
using std::endl;

UINT64 on = 0;
UINT64 off = 0;

VOID docount(BOOL executing)
{
    if (executing)
    {
        on++;  // predicated on
    }
    else
    {
        off++;  // predicated off
    }
}
    
VOID Instruction(INS ins, VOID *v)
{
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)docount, IARG_EXECUTING, IARG_END);
}

VOID Fini(INT32 code, VOID *v)
{
    std::cerr << "total: " << on+off << endl;
    std::cerr << "  predicated on:  " << on << endl;
    std::cerr << "  predicated off: " << off << endl;
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
