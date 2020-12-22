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

/*
This tool is used, in conjuction with inline_opt_test_app, to verify that analysis
functions that are one basic block, but are too long to be inlined are recognized
as setting all the registers that they set
*/

#include "pin.H"


extern "C" void ZeroOutScratches();
extern "C" unsigned int scratchVals[];
unsigned int scratchVals[3];
    
VOID Instruction(INS ins, VOID *v)
{
    
    INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(ZeroOutScratches), IARG_END);
       
}

int main(int argc, char * argv[])
{
    PIN_Init(argc, argv);

    INS_AddInstrumentFunction(Instruction, 0);
    
    // Never returns
    PIN_StartProgram();
    
    return 0;
}

