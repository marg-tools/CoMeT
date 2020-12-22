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

/*! @file
 *  This is an instrumentation-time disassembler that demonstrates the
 *  basics of using the XED interface from within Pin. This tool has no
 *  analysis routines.
 */

#include "pin.H"
extern "C" {
#include "xed-interface.h"
}
#include <iostream>
#include <iomanip>
#include <fstream>
using std::hex;
using std::dec;
using std::setw;
using std::cerr;
using std::endl;

std::ofstream* out = 0;

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

INT32 Usage()
{
    cerr << "This tool prints IA-32 and Intel(R) 64 instructions" << endl;
    cerr << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

VOID Instruction(INS ins, VOID *v)
{
    xed_decoded_inst_t* xedd = INS_XedDec(ins);
    // To print out the gory details uncomment this:
    // char buf[2048];
    // xed_decoded_inst_dump(xedd, buf, 2048);
    // *out << buf << endl;

    xed_syntax_enum_t syntax = XED_SYNTAX_INTEL;  // XED_SYNTAX_ATT, XED_SYNTAX_XED
    const UINT32 BUFLEN = 100;
    char buffer[BUFLEN];
    ADDRINT addr = INS_Address(ins);
    BOOL ok = xed_format_context(syntax, xedd, buffer, BUFLEN, static_cast<UINT64>(addr), 0, 0);
    if (ok)
    {
        *out << setw(sizeof(ADDRINT)*2) 
             << hex << addr << dec << " "  << buffer << endl;
    }
    else
    {
        *out << "disas-error @" << hex << addr << dec << endl;
    }
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char *argv[])
{
    out = new std::ofstream("xed-use.out");
    if( PIN_Init(argc,argv) )
        return Usage();
    INS_AddInstrumentFunction(Instruction, 0);
    PIN_StartProgram();    // Never returns
    return 0;
}

