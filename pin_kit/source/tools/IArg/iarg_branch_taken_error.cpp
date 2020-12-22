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
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

/*
 *************************************************************************
 **                   ###    IMPORTANT NOTE     ###                     **
 **  In the future, if support of instrumenting RTM conditional branch  **
 **  instructions (e.g. XBEGIN, XEND) with IARG_BRANCH_TAKEN will be    **
 **  added to Pin, this test should be removed.                         **
 **  -> View mantis 4504 for more info.                                 **
 *************************************************************************
 */

/*
 *                        #  TOOL DESCRIPTION  #
 * This Pin tool presents wrong usage of instrumenting with IARG_BRANCH_TAKEN:
 * When it is applied on applications that have RTM instructions, it will cause an error.
 */

/* Global Variables */
/* ===================================================================== */
int taken_count = 0;

/* Analysis routines                                                     */
/* ===================================================================== */
VOID analysis(bool is_taken)
{
    if (is_taken)
    {
        taken_count++;
    }
}

/* Instrumentation routines                                              */
/* ===================================================================== */
VOID Instruction(INS ins, VOID *v)
{
    if ((INS_Opcode(ins) == XED_ICLASS_XBEGIN) || (INS_Opcode(ins) == XED_ICLASS_XEND))
    {
        INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR) analysis,
                IARG_BRANCH_TAKEN,
                IARG_END);
    }
}

VOID Fini(INT32 code, VOID *v)
{
    cout << "end of run: taken = " << taken_count << endl;
}

/* =====================================================================
 * Called upon bad command line argument
 * ===================================================================== */
INT32 Usage()
{
    cerr << "This Pin tool presents wrong usage of instrumenting with IARG_BRANCH_TAKEN" << endl;
    cerr << "When it is applied on applications that have RTM instructions, it will cause an error" << endl;
    cerr << KNOB_BASE::StringKnobSummary();
    cerr << endl;
    return -1;
}

/* Main                                                                  */
/* ===================================================================== */
int main(int argc, char *argv[])
{
    if (PIN_Init(argc, argv))
    {
        return Usage();
    };
    PIN_AddFiniFunction(Fini, 0);
    INS_AddInstrumentFunction(Instruction, 0);
    PIN_StartProgram();  // Never returns
    return 0;
}
