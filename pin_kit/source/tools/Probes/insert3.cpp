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
 * Insert a call before a function in probe mode.
 */

/* ===================================================================== */
#include "pin.H"
#include <iostream>
#include <stdlib.h>
#include "tool_macros.h"
using std::dec;
using std::flush;
using std::hex;
using std::cout;
using std::endl;


/* ===================================================================== */
/* Analysis routines  */
/* ===================================================================== */

VOID Before_MyMalloc0( size_t size )
{
    cout << "Before_MyMalloc0: Calling my_malloc() with size=" << size << endl << flush;
}

VOID Before_MyMalloc1( size_t size )
{
    cout << "Before_MyMalloc1: Calling my_malloc() with size=" << size << endl << flush;
}

VOID Before_MyFree0( void * ptr )
{
    cout << "Before_MyFree0: Calling my_free() with ptr=" << hex <<
        (ADDRINT)ptr << dec << endl << flush;
}

VOID Before_MyFree1( void * ptr )
{
    cout << "Before_MyFree1: Calling my_free() with ptr=" << hex <<
        (ADDRINT)ptr << dec << endl << flush;
}



/* ===================================================================== */
/* Instrumentation routines  */
/* ===================================================================== */

VOID Sanity(IMG img, RTN rtn)
{
    if ( PIN_IsProbeMode() && ! RTN_IsSafeForProbedInsertion( rtn ) )
    {
        cout << "Cannot insert calls around " << RTN_Name(rtn) <<
            "() in " << IMG_Name(img) << endl;
        exit(1);
    }
}

/* ===================================================================== */
VOID ImageLoad(IMG img, VOID *v)
{
    if ( ! IMG_IsMainExecutable(img) )
        return;
    
    
    RTN rtn = RTN_FindByName(img, C_MANGLE("my_malloc"));
    if (RTN_Valid(rtn))
    {
        Sanity(img, rtn);
        
        cout << "Inserting 2 calls before my_malloc in " << IMG_Name(img) << endl;

        RTN_InsertCallProbed(
            rtn, IPOINT_BEFORE, AFUNPTR( Before_MyMalloc0 ),
            IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
            IARG_END);

        RTN_InsertCallProbed(
            rtn, IPOINT_BEFORE, AFUNPTR( Before_MyMalloc1 ),
            IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
            IARG_END);
    }

    rtn = RTN_FindByName(img, C_MANGLE("my_free"));
    if (RTN_Valid(rtn))
    {
        Sanity(img, rtn);
        
        cout << "Inserting 2 calls before my_free in " << IMG_Name(img) << endl;

        RTN_InsertCallProbed(
            rtn, IPOINT_BEFORE, AFUNPTR( Before_MyFree0 ),
            IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
            IARG_END);

        RTN_InsertCallProbed(
            rtn, IPOINT_BEFORE, AFUNPTR( Before_MyFree1 ),
            IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
            IARG_END);
    }
}


/* ===================================================================== */

int main(INT32 argc, CHAR *argv[])
{
    PIN_InitSymbols();
    
    PIN_Init(argc, argv);
    
    IMG_AddInstrumentFunction(ImageLoad, 0);
    
    PIN_StartProgramProbed();
    
    return 0;
}



/* ===================================================================== */
/* eof */
/* ===================================================================== */
