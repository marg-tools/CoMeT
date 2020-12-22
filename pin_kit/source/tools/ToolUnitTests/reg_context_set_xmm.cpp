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



#include <assert.h>
#include <stdio.h>
#include "pin.H"


;

VOID AnalysisFunc(CONTEXT *context)
{
    PIN_SetContextReg(context, REG_XMM0, 0);
}

VOID Instruction(INS ins, VOID *v)
{
  	INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)AnalysisFunc, IARG_CONTEXT, IARG_END);
    
}


int main(int argc, char * argv[])
{
    PIN_Init(argc, argv);

    INS_AddInstrumentFunction(Instruction, 0);

    PIN_StartProgram();
    
    return 0;
}
