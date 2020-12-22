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
#include <iostream>
using std::endl;

// This tool shows how to detach Pin from an 
// application that is under Pin's control.

UINT64 icount = 0;
VOID docount() 
{
    icount++;

    // Release control of application if 10000 
    // instructions have been executed
    if ((icount % 10000) == 0) 
    {
        PIN_Detach();
    }
}
 
VOID Instruction(INS ins, VOID *v)
{
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)docount, IARG_END);
}

VOID HelloWorld(VOID *v)
{
    std::cerr << "Hello world!" << endl;
}

VOID ByeWorld(VOID *v)
{
    std::cerr << "Byebye world!" << endl;
}

VOID Fini(INT32 code, VOID *v)
{
    std::cerr << "Count: " << icount << endl;
}

int main(int argc, char * argv[])
{
    PIN_Init(argc, argv);

    // Callback function to invoke for every 
    // execution of an instruction
    INS_AddInstrumentFunction(Instruction, 0);
    
    // Callback functions to invoke before
    // Pin releases control of the application
    PIN_AddDetachFunction(HelloWorld, 0);
    PIN_AddDetachFunction(ByeWorld, 0);

    PIN_AddFiniFunction(Fini, 0);
    
    // Never returns
    PIN_StartProgram();
    
    return 0;
}
