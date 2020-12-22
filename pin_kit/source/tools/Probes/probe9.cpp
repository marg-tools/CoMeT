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
 */

#include "pin.H"
#include <iostream>
#include <fstream>
#include <stdlib.h>
using std::cout;
using std::ios;
using std::hex;
using std::cerr;
using std::ofstream;
using std::endl;
using std::string;


/* ===================================================================== */
/* Global Variables */
/* ===================================================================== */

ofstream TraceFile;
static void (*pf_dn)();


/* ===================================================================== */
/* Commandline Switches */
/* ===================================================================== */

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "probe9.outfile", "specify file name");

/* ===================================================================== */

INT32 Usage()
{
    cerr <<
        "This pin tool tests probe replacement.\n"
        "\n";
    cerr << KNOB_BASE::StringKnobSummary();
    cerr << endl;
    return -1;
}


void Foo_Function()
{
    if (pf_dn)
    {
        (*pf_dn)();
        
        TraceFile << "Shorty replacement." << endl;
    }
}

/* ===================================================================== */
// Called every time a new image is loaded
// Look for routines that we want to probe
VOID ImageLoad(IMG img, VOID *v)
{
    cout << "Processing " << IMG_Name( img ) << endl;
    
    RTN rtn = RTN_FindByName(img, "shorty");
    if (RTN_Valid(rtn))
    {
        if ( ! RTN_IsSafeForProbedReplacement( rtn ) )
        {
            TraceFile << "Cannot replace " << RTN_Name(rtn) << " in " << IMG_Name(img) << endl;
            exit(1);
        }

        pf_dn = (void (*)())RTN_ReplaceProbed( rtn, AFUNPTR( Foo_Function ) );

        TraceFile << "Inserted probe for shorty:" << IMG_Name(img) << endl;
    }

    cout << "Completed " << IMG_Name( img ) << endl;
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
    
    PIN_StartProgramProbed();
    
    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
