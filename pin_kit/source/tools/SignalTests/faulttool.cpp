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
 * This test verifies that Pin gives an error message if an inlined anlaysis
 * function causes a fault.
 */

#include "pin.H"

static VOID InstrumentInstruction(INS, VOID *);
static void OnInstruction(VOID *);


int main(int argc, char * argv[])
{
    PIN_Init(argc, argv);

    INS_AddInstrumentFunction(InstrumentInstruction, 0);

    PIN_StartProgram();
    return 0;
}


static VOID InstrumentInstruction(INS ins, VOID *v)
{
    INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(OnInstruction), IARG_PTR, (void*)16, IARG_END);
}


// The test assumes that OnInstruction is inline-able by pin.
static void OnInstruction(VOID *ptr)
{
    // Generate a fault.
    //
    *(int *)ptr = 0;
}
