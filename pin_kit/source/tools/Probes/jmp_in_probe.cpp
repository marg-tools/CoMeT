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


/* ===================================================================== */
/*! @file
  Replaces probed_func that has a branch within the bytes which must be overwritten
 */

#include <stdlib.h>
 
#include "pin.H"
#include <iostream>
#include <fstream>

using std::cerr;
using std::endl;
using std::cout;
using std::flush;

/* ===================================================================== */
/* Global Variables */
/* ===================================================================== */


typedef int (*FUNCPTR)(int);
static int (*pf_jmp_in_probe)(int num);


/* ===================================================================== */

INT32 Usage()
{
    cerr <<
        "This pin tool replaces probed_func()\n"
        "\n";
    cerr << KNOB_BASE::StringKnobSummary();
    cerr << endl;
    return -1;
}


/* ===================================================================== */

int ToolReplacementFunc(int num)
{
    cout << "ToolReplacementFunc: calling probed_func()" << endl << flush;
    int retVal = (pf_jmp_in_probe)(num);
    cout << "ToolReplacementFunc: back from probed_func()" << endl << flush;
    return retVal;
}


/* ===================================================================== */

// Called every time a new image is loaded.
// Look for routines that we want to replace.
VOID ImageLoad(IMG img, VOID *v)
{
    RTN rtn = RTN_FindByName(img, "probed_func");

    if ( RTN_Valid(rtn))
    {
        if ( RTN_IsSafeForProbedReplacementEx(rtn, PROBE_MODE_ALLOW_RELOCATION) )
        {
            
            // Save the function pointer that points to the new location of
            // the entry point of the original exit in this image.
            //
            pf_jmp_in_probe = (FUNCPTR)RTN_ReplaceProbedEx( rtn, PROBE_MODE_ALLOW_RELOCATION, 
                            AFUNPTR( ToolReplacementFunc ));
            
            cout << "ImageLoad: Replaced probed_func() in:"  << IMG_Name(img) << endl;
        }
        else
        {
            cout << "ImageLocad: Can't replace probed_func() in:"  << IMG_Name(img) << endl;
            exit(-1);
        }
    }
}


/* ===================================================================== */

int main(int argc, CHAR *argv[])
{
    PIN_InitSymbols();

    if( PIN_Init(argc,argv) )
        return Usage();

    IMG_AddInstrumentFunction(ImageLoad, 0);
    
    PIN_StartProgramProbed();
    
    return 0;
}


/* ===================================================================== */
/* eof */
/* ===================================================================== */
