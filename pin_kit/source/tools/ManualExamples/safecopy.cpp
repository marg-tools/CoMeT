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

#include <stdio.h>
#include "pin.H"
#include <iostream>
#include <fstream>
using std::cerr;
using std::endl;

std::ofstream* out = 0;

//=======================================================
//  Analysis routines
//=======================================================

// Move from memory to register
ADDRINT DoLoad(REG reg, ADDRINT * addr)
{
    *out << "Emulate loading from addr " << addr << " to " << REG_StringShort(reg) << endl;
    ADDRINT value;
    PIN_SafeCopy(&value, addr, sizeof(ADDRINT));
    return value;
}

//=======================================================
// Instrumentation routines
//=======================================================

VOID EmulateLoad(INS ins, VOID* v)
{
    // Find the instructions that move a value from memory to a register
    if (INS_Opcode(ins) == XED_ICLASS_MOV &&
        INS_IsMemoryRead(ins) &&
        INS_OperandIsReg(ins, 0) &&
        INS_OperandIsMemory(ins, 1))
    {
        // op0 <- *op1
        INS_InsertCall(ins,
                       IPOINT_BEFORE,
                       AFUNPTR(DoLoad),
                       IARG_UINT32,
                       REG(INS_OperandReg(ins, 0)),
                       IARG_MEMORYREAD_EA,
                       IARG_RETURN_REGS,
                       INS_OperandReg(ins, 0),
                       IARG_END);

        // Delete the instruction
        INS_Delete(ins);
    }
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

INT32 Usage()
{
    cerr << "This tool demonstrates the use of SafeCopy" << endl;
    cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char * argv[])
{
    // Write to a file since cout and cerr maybe closed by the application
    out = new std::ofstream("safecopy.out");

    // Initialize pin & symbol manager
    if (PIN_Init(argc, argv)) return Usage();
    PIN_InitSymbols();

    // Register EmulateLoad to be called to instrument instructions
    INS_AddInstrumentFunction(EmulateLoad, 0);

    // Never returns
    PIN_StartProgram();
    return 0;
}
