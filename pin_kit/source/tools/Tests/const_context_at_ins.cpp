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
Tool that requests IARG_CONST_CONTEXT at each instruction
*/
#include <cstdio>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "pin.H"
#include "instlib.H"


VOID GetSomeIntRegsFromContext (CONTEXT *ctxt)
{
    PIN_GetContextReg( ctxt, REG_INST_PTR );

    PIN_GetContextReg( ctxt, REG_GAX );

    PIN_GetContextReg( ctxt, REG_GBX );

}

VOID ReceiveContext (CONTEXT *ctxt)
{
    GetSomeIntRegsFromContext(ctxt);
}




VOID Instruction(INS ins, VOID *v)
{
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR) ReceiveContext,   IARG_CONST_CONTEXT, IARG_END);
}



int main(int argc, char *argv[])
{
    PIN_Init(argc,argv);

    INS_AddInstrumentFunction(Instruction, 0);

    // Never returns
    PIN_StartProgram();

    return 0;
}
