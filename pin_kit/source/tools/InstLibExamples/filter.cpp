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

#include <iomanip>
#include <iostream>

#include "pin.H"
#include "instlib.H"
using std::ofstream;
using std::hex;
using std::setw;

using namespace INSTLIB;

// Contains knobs to filter out things to instrument
FILTER filter;

ofstream out;
KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "filter.out", "specify output file name");

INT32 Usage()
{
    cerr <<
        "This pin tool demonstrates use of FILTER to identify instrumentation points\n"
        "\n";

    cerr << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

VOID Trace(TRACE trace, VOID * val)
{
    if (!filter.SelectTrace(trace))
        return;

    for (BBL bbl = TRACE_BblHead(trace); BBL_Valid(bbl); bbl = BBL_Next(bbl))
    {
        for (INS ins = BBL_InsHead(bbl); INS_Valid(ins); ins = INS_Next(ins))
        {
            out << hex << setw(8) << INS_Address(ins) << " ";
    
            RTN rtn = TRACE_Rtn(trace);
            if (RTN_Valid(rtn))
            {
                IMG img = SEC_Img(RTN_Sec(rtn));
                if (IMG_Valid(img)) {
                    out << IMG_Name(img) << ":" << RTN_Name(rtn) << " " ;
                }
            }
    
            out << INS_Disassemble(ins) << endl;
        }
    }
}

VOID Fini(INT32 code, VOID * junk)
{
    out.close();
}

// argc, argv are the entire command line, including pin -t <toolname> -- ...
int main(int argc, char * argv[])
{
    if( PIN_Init(argc,argv) )
    {
        return Usage();
    }

    out.open(KnobOutputFile.Value().c_str());

    TRACE_AddInstrumentFunction(Trace, 0);
    
    filter.Activate();

    PIN_AddFiniFunction(Fini, NULL);
    
    // Start the program, never returns
    PIN_StartProgram();
    return 0;
}


