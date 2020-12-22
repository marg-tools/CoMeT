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

//
// Check that Pin gets the error file information correct
// when a bad argument is given to an instrumentation function.
//
#include "pin.H"

void doNothing(ADDRINT)
{
}

void Instruction(INS ins, VOID *)
{
    if (INS_IsMemoryRead(ins))
    {
        // IARG_MEMORYREAD_EA is not valid at IPOINT_AFTER. We're going to check the error message, 
        // to make sure that it points to the next line, which is line 17 (or 47 once the legal header is added)
        INS_InsertCall(ins, IPOINT_AFTER, (AFUNPTR)doNothing, IARG_MEMORYREAD_EA, IARG_END);
    }
}

// argc, argv are the entire command line, including pin -t <toolname> -- ...
int main(int argc, char * argv[])
{
    if( PIN_Init(argc,argv) )
    {
        return -1;
    }
    
    INS_AddInstrumentFunction(Instruction, 0);

    // Start the program, never returns
    PIN_StartProgram();
    
    return 0;
}


