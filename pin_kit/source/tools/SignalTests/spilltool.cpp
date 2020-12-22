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
 * This tool inserts instrumentation before every instruction
 *
 * When the instrumentation is not inlined, it forces the xmm registers to
 * be spilled. This is used to test construction of a context during a
 * synchronous signal when xmm registers are spilled
 *
 */

#include <pin.H>

int n = 0;

void Spill()
{
}

void Ins(INS ins, VOID *)
{
    INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(Spill), IARG_END);
}

int main(int argc, char * argv[])
{
    PIN_Init(argc, argv);

    INS_AddInstrumentFunction(Ins, 0);

    PIN_StartProgram();
    return 0;
}
