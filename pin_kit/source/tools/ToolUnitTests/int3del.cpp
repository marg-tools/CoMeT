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

#include "pin.H"

VOID delete_int3(INS ins, VOID* v)
{
    if (INS_Opcode(ins) == XED_ICLASS_INT3)
    {
        INS_Delete(ins);
    }
}

int main(int argc, char * argv[])
{
    PIN_Init(argc, argv);
    INS_AddInstrumentFunction(delete_int3, 0);
    PIN_StartProgram();    // Never returns
    return 0;
}
