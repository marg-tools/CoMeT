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
This tool is used in conjuction with the inline_opt_test_df_app to verify that an analysis routine
that is 1 BBL but is too long to inline, that sets the DF flag is recognized by Pin as setting the DF
dlaf
*/
#include "pin.H"


extern "C" void SetDf();

    
VOID Instruction(INS ins, VOID *v)
{
    
    INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(SetDf), IARG_END);
       
}

int main(int argc, char * argv[])
{
    PIN_Init(argc, argv);

    INS_AddInstrumentFunction(Instruction, 0);
    
    // Never returns
    PIN_StartProgram();
    
    return 0;
}

