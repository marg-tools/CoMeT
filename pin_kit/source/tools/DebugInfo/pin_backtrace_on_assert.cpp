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

#include <iostream>
#include "pin.H"


VOID DoASSERT()
{
    ASSERTX(FALSE);
}

VOID Bar()
{
    DoASSERT();
}

VOID Foo()
{
    Bar();
}

VOID Instruction(INS ins, void *v)
{
    Foo();
}

/* ================================================================== */
/*
 Initialize and begin program execution under the control of Pin
*/
int main(INT32 argc, CHAR **argv)
{
    PIN_Init(argc, argv);

    PIN_InitSymbols();

    INS_AddInstrumentFunction(Instruction, 0);

    PIN_StartProgram();

    return 0;
}
