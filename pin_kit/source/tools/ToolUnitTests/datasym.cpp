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
#include <fstream>
#include <string.h>


using std::ofstream;
using std::string;
using std::cerr;
using std::endl;
using std::cout;
using std::ios;
using std::hex;

/* ===================================================================== */
/* Global Variables */
/* ===================================================================== */

ofstream TraceFile;


/* ===================================================================== */
/* Commandline Switches */
/* ===================================================================== */

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "symbolnames.outfile", "specify trace file name");

/* ===================================================================== */

INT32 Usage()
{
    cerr <<
        "This pin tool collects an instruction trace for debugging\n"
        "\n";
    cerr << KNOB_BASE::StringKnobSummary();
    cerr << endl;
    return -1;
}


VOID ImageLoad(IMG img, VOID *v)
{
    if (IMG_IsMainExecutable(img))
    {
        TraceFile << "Processing " << IMG_Name(img) << endl;
        cout << "Processing " << IMG_Name(img) << endl;

        for (SYM sym = IMG_RegsymHead (img); SYM_Valid(sym); sym = SYM_Next(sym) ) {
            TraceFile << "   " << SYM_Name(sym) << endl;
        }

        cout << "Completed " << IMG_Name(img) << endl;
    }
}


/* ===================================================================== */

int main(int argc, CHAR *argv[])
{
    PIN_InitSymbols();

    if( PIN_Init(argc,argv) )
    {
        return Usage();
    }

    TraceFile.open(KnobOutputFile.Value().c_str());
    TraceFile << hex;
    TraceFile.setf(ios::showbase);

    IMG_AddInstrumentFunction(ImageLoad, 0);

    PIN_StartProgram();

    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
