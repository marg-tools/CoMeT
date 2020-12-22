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
 * Insert a call before/after pthread_spin_lock() in probe mode.
 * Linux IA-32 / Intel(R) 64 architectures only.
 */

/* ===================================================================== */
#include "pin.H"
#include <cstdlib>
#include <iostream>
using std::flush;
using std::cout;
using std::endl;


/* ===================================================================== */
/* Analysis routines  */
/* ===================================================================== */

VOID Before( ADDRINT * lock )
{
    cout << "Before: lock = " << *lock << endl << flush;
}


VOID After( ADDRINT retval )
{
    cout << "After: return value = " << retval << endl << flush;
}


/* ===================================================================== */
/* Instrumentation routines  */

/* ===================================================================== */
VOID ImageLoad(IMG img, VOID *v)
{
    RTN rtn = RTN_FindByName(img, "pthread_spin_lock");

    if ( RTN_Valid(rtn) && RTN_IsSafeForProbedReplacementEx(rtn, PROBE_MODE_ALLOW_RELOCATION) )
    {
        PROTO proto = PROTO_Allocate( PIN_PARG(int), CALLINGSTD_DEFAULT,
                                      "pthread_spin_lock", PIN_PARG(void *),
                                      PIN_PARG_END() );
        
        RTN_InsertCallProbedEx(
            rtn, IPOINT_BEFORE, 
            PROBE_MODE_ALLOW_RELOCATION, AFUNPTR( Before ),
            IARG_PROTOTYPE, proto,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
            IARG_END);

        RTN_InsertCallProbedEx(
            rtn, IPOINT_AFTER, 
            PROBE_MODE_ALLOW_RELOCATION, AFUNPTR( After ),
            IARG_PROTOTYPE, proto,
            IARG_REG_VALUE, REG_GAX,
            IARG_END);

        PROTO_Free( proto );
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
