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

#include <fstream>
#include "pin.H"
using std::string;

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool", "o", "int3-count.out", "log file");
KNOB<string> KnobFunction(KNOB_MODE_WRITEONCE, "pintool", "func", "", "function to trace");


static void InstrumentIns(INS, VOID *);
static void OnExit(INT32, VOID *);
static void CountInt3();
static void CountOther();


static UINT64 NumInt3 = 0;
static UINT64 NumOther = 0;


int main(int argc, char * argv[])
{
    PIN_Init(argc, argv);
    PIN_InitSymbols();

    INS_AddInstrumentFunction(InstrumentIns, 0);
    PIN_AddFiniFunction(OnExit, 0);

    PIN_StartProgram();
    return 0;
}


static void InstrumentIns(INS ins, VOID *)
{
    RTN rtn = INS_Rtn(ins);
    if (!RTN_Valid(rtn) || RTN_Name(rtn) != KnobFunction.Value())
        return;

    if (INS_Opcode(ins) == XED_ICLASS_INT3)
        INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(CountInt3), IARG_END);
    else
        INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(CountOther), IARG_END);
}

static void OnExit(INT32, VOID *)
{
    std::ofstream out(KnobOutputFile.Value().c_str());

    out << "Total count: " << NumOther + NumInt3 << std::endl;
    out << "INT3 count : " << NumInt3 << std::endl;
}

static void CountInt3()
{
    NumInt3++;
}

static void CountOther()
{
    NumOther++;
}
