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

#include <cstdio>
#include "pin.H"

UINT64 icount = 0;

ADDRINT SwizzleAddress(ADDRINT val)
{
    return val;
}


VOID Instruction(INS ins, VOID *v)
{
    REG basereg = INS_dec(ins)->basereg;

    if (basereg == REG_INVALID())
        return;

    // Not allowed to change esp
    if (basereg == REG_ESP)
        return;

    INS_InsertCall(ins, IPOINT_BEFORE,
                   (AFUNPTR)SwizzleAddress, IARG_REG_VALUE, basereg, IARG_RETURN_REGS, basereg, IARG_END);
}

int main(int argc, char * argv[])
{
    PIN_Init(argc, argv);

    INS_AddInstrumentFunction(Instruction, 0);

    // Never returns
    PIN_StartProgram();

    return 0;
}
