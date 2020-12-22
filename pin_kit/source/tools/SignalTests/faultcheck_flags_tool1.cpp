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
#include <fstream>
#include "pin.H"
// This tool inserts instructions that set the status flags before each instruction

// The running count of instructions is kept here
// make it static to help the compiler optimize docount
static UINT64 icount = 0;

// This function is called before every instruction
// Use the fast linkage for calls
VOID PIN_FAST_ANALYSIS_CALL docount(ADDRINT c) { icount += c; }
    


VOID Instruction(INS ins, VOID *v)
{
    
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)docount, IARG_FAST_ANALYSIS_CALL, IARG_UINT32, 1, IARG_END);
}



// argc, argv are the entire command line, including pin -t <toolname> -- ...
int main(int argc, char * argv[])
{
    // Initialize pin
    PIN_Init(argc, argv);

    // Register Instruction to be called to instrument instructions
    INS_AddInstrumentFunction(Instruction, 0);
    
    // Start the program, never returns
    PIN_StartProgram();
    
    return 0;
}
