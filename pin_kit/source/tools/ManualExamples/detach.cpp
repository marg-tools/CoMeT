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
using std::cerr;
using std::endl;

// This tool shows how to detach Pin from an 
// application that is under Pin's control.

UINT64 icount = 0;

#define N 10000
VOID docount() 
{
    icount++;

    // Release control of application if 10000 
    // instructions have been executed
    if ((icount % N) == 0) 
    {
        PIN_Detach();
    }
}
 
VOID Instruction(INS ins, VOID *v)
{
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)docount, IARG_END);
}

VOID ByeWorld(VOID *v)
{
    std::cerr << endl << "Detached at icount = " << N << endl;
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

INT32 Usage()
{
    cerr << "This tool demonstrates how to detach Pin from an " << endl;
    cerr << "application that is under Pin's control" << endl;
    cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char * argv[])
{
    if (PIN_Init(argc, argv)) return Usage();

    // Callback function to invoke for every 
    // execution of an instruction
    INS_AddInstrumentFunction(Instruction, 0);
    
    // Callback functions to invoke before
    // Pin releases control of the application
    PIN_AddDetachFunction(ByeWorld, 0);
    
    // Never returns
    PIN_StartProgram();
    
    return 0;
}
