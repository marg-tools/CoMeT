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

/* ===================================================================== */
/*! @file
  Replaces pthread_spin_lock(). Linux only, of course.
 */
#include <stdlib.h>
#include "pin.H"
#include <iostream>
#include <fstream>
using std::hex;
using std::dec;
using std::cerr;
using std::endl;
using std::cout;


/* ===================================================================== */
/* Global Variables */
/* ===================================================================== */

// Don't use pthread_spinlock_t* in pthread_spin_lock signature since
// our pthread_spin_lock type may be different than the application's libc
// pthread_spin_lock.
typedef int (*FUNCPTR)(void *);


/* ===================================================================== */

INT32 Usage()
{
    cerr <<
        "This pin tool replaces pthread_spin_lock()\n"
        "\n";
    cerr << KNOB_BASE::StringKnobSummary();
    cerr << endl;
    return -1;
}


/* ===================================================================== */

int SpinLock( FUNCPTR orgFuncptr, void * lock)
{
    cout << "SpinLock: calling pthread_spin_lock() at address " << hex << (ADDRINT)orgFuncptr << dec << endl;

    int locked = orgFuncptr(lock);

    cout << "Spinlock: returned from pthread_spin_lock()." << endl;

    return locked;
}

/* ===================================================================== */

// Called every time a new image is loaded.
// Look for routines that we want to replace.
VOID ImageLoad(IMG img, VOID *v)
{
    RTN rtn = RTN_FindByName(img, "pthread_spin_lock");

    if ( RTN_Valid(rtn) )
    {
        if (RTN_IsSafeForProbedReplacementEx(rtn, PROBE_MODE_ALLOW_RELOCATION) )
        {
            PROTO proto = PROTO_Allocate( PIN_PARG(int), CALLINGSTD_DEFAULT,
                                        "pthread_spin_lock", PIN_PARG(void *),
                                        PIN_PARG_END() );
            
#if defined ( TARGET_IA32 ) || defined ( TARGET_IA32E )
        
            RTN_ReplaceSignatureProbedEx(
                rtn, PROBE_MODE_ALLOW_RELOCATION,
                AFUNPTR( SpinLock ),
                IARG_PROTOTYPE, proto,
                IARG_ORIG_FUNCPTR,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                IARG_END);
#else

            RTN_ReplaceSignatureProbedEx(
                rtn, PROBE_MODE_ALLOW_RELOCATION,
                AFUNPTR( SpinLock ),
                IARG_PROTOTYPE, proto,
                IARG_ORIG_FUNCPTR,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                IARG_REG_VALUE, REG_TP,
                IARG_END);
#endif
            cout << "ImageLoad: Replaced pthread_spin_lock() in:"  << IMG_Name(img) << endl;
        }
        else
        {
            cout << "ImageLoad: Can't replace pthread_spin_lock() in:"  << IMG_Name(img) << endl;
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
