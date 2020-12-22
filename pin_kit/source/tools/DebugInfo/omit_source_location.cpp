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


/* =====================================================================
 * This PIN tools instruments instructions in an invalid way such
 * that it will trigger an assertion.
 * The assertion that will be triggered is defined by the tool's command
 * line argument "-e" and can assume 3 possible values:
 * 0 - No assertion triggered
 * 1 - Triggers the assertion: IARG_MEMORY*_EA is only valid at IPOINT_BEFORE
 * 2 - Triggers the assertion: IARG_MEMORYOP_EA/IARG_MEMORYOP_MASKED_ON invalid memory operand index
   ===================================================================== */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "pin.H"
using std::ofstream;
using std::cerr;
using std::endl;

KNOB<int> KnobAssertionNumber(KNOB_MODE_WRITEONCE, "pintool",
    "e", "0", "specify assertion number to trigger (0 - 2)");
ofstream OutFile;

static UINT64 icount = 0;

VOID docount() { icount++; }


// Pin calls this function every time a new instruction is encountered
VOID Instruction(INS ins, VOID *v)
{
    switch (KnobAssertionNumber.Value())
    {
        case 0:
            // No assertion triggered
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)docount, IARG_END);
            break;
        case 1:
            // Triggers the assertion: IARG_MEMORY*_EA is only valid at IPOINT_BEFORE
            if (INS_IsMemoryRead(ins))
            {
                INS_InsertCall(ins, IPOINT_AFTER, (AFUNPTR)docount, IARG_MEMORYREAD_EA, IARG_END);
            }
            break;
        case 2:
            // Triggers the assertion: IARG_MEMORYOP_EA/IARG_MEMORYOP_MASKED_ON invalid memory operand index
            // by trying to pass an out of range operand number to the analysis routine
            if (INS_IsMemoryRead(ins))
            {
                INS_InsertCall(ins, IPOINT_AFTER, (AFUNPTR)docount, IARG_MEMORYOP_EA, INS_MemoryOperandCount(ins) + 1, IARG_END);
            }
            break;
    }
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

INT32 Usage()
{
    cerr << "This tool triggers an assertion in various ways" << endl;
    cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

int main(int argc, char **argv)
{
    if (PIN_Init(argc, argv))
    {
        Usage();
        return EXIT_FAILURE;
    }
    if (KnobAssertionNumber.Value() < 0 || KnobAssertionNumber.Value() > 2)
    {
        cerr << "Assertion number must be between 0 to 2" << endl;
        return EXIT_FAILURE;
    }

    INS_AddInstrumentFunction(Instruction, NULL);

    PIN_StartProgram();
    return EXIT_FAILURE;
}
