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

/*
This tool is used to check that the flags set by the tool do
not overwrite the application flags
*/

// This function is called before every instruction is executed
// It sets the DF,SF,ZF,PF,AF and CF to 0
#if defined(__cplusplus)
extern "C"
#endif
VOID ZeroAppFlags_asm ();



    
// Pin calls this function every time a new instruction is encountered
VOID Instruction(INS ins, VOID *v)
{
    
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)ZeroAppFlags_asm, IARG_END);
}

// This function is called when the application exits
VOID Fini(INT32 code, VOID *v)
{
    
}

// argc, argv are the entire command line, including pin -t <toolname> -- ...
int main(int argc, char * argv[])
{
    // Initialize pin
    PIN_Init(argc, argv);

    // Register Instruction to be called to instrument instructions
    INS_AddInstrumentFunction(Instruction, 0);

    // Register Fini to be called when the application exits
    PIN_AddFiniFunction(Fini, 0);
    
    // Start the program, never returns
    PIN_StartProgram();
    
    return 0;
}
