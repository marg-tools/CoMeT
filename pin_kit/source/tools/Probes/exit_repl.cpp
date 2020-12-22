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
  Replaces pthread_spin_lock(). Linux only, of course.
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

typedef void  (*FUNCPTR)(int status);
static void  (*pf_exit)(int status);


/* ===================================================================== */

INT32 Usage()
{
    cerr <<
        "This pin tool replaces exit() function in libc\n"
        "\n";
    cerr << KNOB_BASE::StringKnobSummary();
    cerr << endl;
    return -1;
}


/* ===================================================================== */

void MyExit(int arg)
{
    cout << "MyExit: calling original exit() from libc" << endl;

    return (pf_exit)(arg);
}


/* ===================================================================== */

// Called every time a new image is loaded.
// Look for routines that we want to replace.
VOID ImageLoad(IMG img, VOID *v)
{
    RTN rtn = RTN_FindByName(img, C_MANGLE("exit"));

    if ( RTN_Valid(rtn))
    {
        //fprintf(stderr, "Attach to prs %d\n", PIN_GetPid());
        //getchar();
        if (RTN_IsSafeForProbedReplacementEx(rtn, PROBE_MODE_ALLOW_RELOCATION))
        {        
            // Save the function pointer that points to the new location of
            // the entry point of the original exit in this image.
            //
            pf_exit = (FUNCPTR)RTN_ReplaceProbedEx( rtn, PROBE_MODE_ALLOW_RELOCATION, AFUNPTR(MyExit));
            
            cout << "ImageLoad: Replaced exit() in: "  << IMG_Name(img) << endl;
    	}
        else
        {
            cout << "ImageLoad: Pin can't replace exit() in: "  << IMG_Name(img) << endl;
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
