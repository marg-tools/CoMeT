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

// This tool tests the IARG_UINT64 argument type


#include <iostream>
#include <fstream>
#include "pin.H"
using std::cout;
using std::hex;
using std::cerr;
using std::ostream;
using std::endl;
using std::string;

#define CONST_U32_1 0x11111111UL
#define CONST_U32_2 0x22222222UL
#define CONST_U64_1 0x3333333344444444ULL

ostream *OutFile;

/* ===================================================================== */
/* Command line switches                                                 */
/* ===================================================================== */

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
                            "o", "", "Specify file name for the tool's output. If no filename is specified,"
                            " the output will be directed to stdout.");

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

INT32 Usage()
{
    cerr << "This tool tests the IARG_UINT64 argument type." << endl;
    cerr << KNOB_BASE::StringKnobSummary() << endl;
    return 1;
}

VOID AtIns1(UINT64 arg1, UINT32 arg2, UINT32 arg3)
{
    *OutFile << arg1 << "," << arg2 << "," << arg3 << endl;
}

VOID PIN_FAST_ANALYSIS_CALL AtIns2(UINT64 arg1, UINT32 arg2, UINT32 arg3)
{
    *OutFile << arg1 << "," << arg2 << "," << arg3 << endl;
}

VOID AtIns3(UINT32 arg1, UINT64 arg2, UINT32 arg3)
{
    *OutFile << arg1 << "," << arg2 << "," << arg3 << endl;
}

VOID PIN_FAST_ANALYSIS_CALL AtIns4(UINT32 arg1, UINT64 arg2, UINT32 arg3)
{
    *OutFile << arg1 << "," << arg2 << "," << arg3 << endl;
}

VOID AtIns5(UINT32 arg1, UINT32 arg2, UINT64 arg3)
{
    *OutFile << arg1 << "," << arg2 << "," << arg3 << endl;
}

VOID PIN_FAST_ANALYSIS_CALL AtIns6(UINT32 arg1, UINT32 arg2, UINT64 arg3)
{
    *OutFile << arg1 << "," << arg2 << "," << arg3 << endl;
    PIN_ExitApplication(0);
}


VOID Instruction(INS ins, void *v)
{
    INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(AtIns1), IARG_UINT64, CONST_U64_1, IARG_UINT32, CONST_U32_1, IARG_UINT32, CONST_U32_2, IARG_END);
    INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(AtIns2), IARG_FAST_ANALYSIS_CALL, IARG_UINT64, CONST_U64_1, IARG_UINT32, CONST_U32_1, IARG_UINT32, CONST_U32_2, IARG_END);
    INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(AtIns3), IARG_UINT32, CONST_U32_1, IARG_UINT64, CONST_U64_1, IARG_UINT32, CONST_U32_2, IARG_END);
    INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(AtIns4), IARG_FAST_ANALYSIS_CALL, IARG_UINT32, CONST_U32_1, IARG_UINT64, CONST_U64_1, IARG_UINT32, CONST_U32_2, IARG_END);
    INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(AtIns5), IARG_UINT32, CONST_U32_1, IARG_UINT32, CONST_U32_2, IARG_UINT64, CONST_U64_1, IARG_END);
    INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(AtIns6), IARG_FAST_ANALYSIS_CALL, IARG_UINT32, CONST_U32_1, IARG_UINT32, CONST_U32_2, IARG_UINT64, CONST_U64_1, IARG_END);
}


int main(int argc, char **argv)
{
    if( PIN_Init(argc,argv) ) {
        return Usage();
    }

    OutFile = KnobOutputFile.Value().empty() ? &cout : new std::ofstream(KnobOutputFile.Value().c_str());
    *OutFile << hex;

    INS_AddInstrumentFunction(Instruction, 0);

    PIN_StartProgram();
    return 0;
}
