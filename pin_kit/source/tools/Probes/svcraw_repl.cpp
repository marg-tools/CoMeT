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
  Replaces svcraw_create(). Linux only, of course.
  On some OSes this routine can be probed only if Pin
  moves the whole routine to another place
 */

#include "pin.H"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "tool_macros.h"
using std::cerr;
using std::endl;
using std::cout;


/* ===================================================================== */
/* Global Variables */
/* ===================================================================== */

typedef void * (*FUNCPTR)();
static void * (*pf_svcraw_create)();


/* ===================================================================== */

INT32 Usage()
{
    cerr <<
        "This pin tool replaces svcraw_create()\n"
        "\n";
    cerr << KNOB_BASE::StringKnobSummary();
    cerr << endl;
    return -1;
}


/* ===================================================================== */

void *SvcrawCreate(void *arg)
{
    cout << "SvcrawCreate: calling original svcraw_create() from libc" << endl;

    return (pf_svcraw_create)();
}


/* ===================================================================== */

// Called every time a new image is loaded.
// Look for routines that we want to replace.
VOID ImageLoad(IMG img, VOID *v)
{
    RTN rtn = RTN_FindByName(img, C_MANGLE("svcraw_create"));

    if ( RTN_Valid(rtn))
    {
        // fprintf(stderr, "Attach to prs %d\n", PIN_GetPid());
        // getchar();
        if (RTN_IsSafeForProbedReplacementEx(rtn, PROBE_MODE_ALLOW_RELOCATION))
        {        
            // Save the function pointer that points to the new location of
            // the entry point of the original exit in this image.
            //
            pf_svcraw_create = (FUNCPTR)RTN_ReplaceProbedEx( rtn, PROBE_MODE_ALLOW_RELOCATION, AFUNPTR(SvcrawCreate));
            
            cout << "ImageLoad: Replaced svcraw_create() in: "  << IMG_Name(img) << endl;
    	}
        else
        {
            cout << "ImageLoad: Pin can't replace svcraw_create() in: "  << IMG_Name(img) << endl;
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
