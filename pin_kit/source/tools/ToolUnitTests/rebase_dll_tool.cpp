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

//
// This tool prints a trace of image load and unload events
//

#include "pin.H"
#include <stdio.h>

using std::string;

FILE * trace;

static KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool", 
    "o", "imageload.out", "Output file");

// Pin calls this function every time a new img is loaded
VOID ImageLoad(IMG img, VOID *v)
{
    SEC sec;
    RTN rtn;

    if ( string::npos == IMG_Name(img).find( "dummy_dll" ) ) 
        return;

    fprintf(trace, "library: %s\n", IMG_Name(img).c_str() );

    for ( sec = IMG_SecHead(img); SEC_Valid(sec); sec = SEC_Next(sec) ) 
        for ( rtn = SEC_RtnHead(sec); RTN_Valid(rtn); rtn = RTN_Next(rtn) )
            fprintf(trace, "rtn: %s\n", RTN_Name(rtn).c_str() );

    fflush(trace);
}

// argc, argv are the entire command line, including pin -t <toolname> -- ...
int main(int argc, char * argv[])
{
    // Initialize symbol processing
    PIN_InitSymbols();
    
    // Initialize pin
    if (PIN_Init(argc, argv) != 0)
    {
        return 1;
    }

    trace = fopen(KnobOutputFile.Value().c_str(), "w");

    // Register ImageLoad to be called when an image is loaded
    IMG_AddInstrumentFunction(ImageLoad, 0);

    // Start the program, never returns
    if (PIN_IsProbeMode()) 
    {
        fprintf(trace, "Probe mode\n");
        PIN_StartProgramProbed();
    } else 
    {
        fprintf(trace, "JIT mode\n");
        PIN_StartProgram();
    }

    return 0;
}
