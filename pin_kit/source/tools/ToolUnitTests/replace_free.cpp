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
  Generates a trace of malloc/free calls
 */

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
typedef VOID (*FUNCPTR_FREE)(void *);

VOID   Jit_Free_IA32( CONTEXT * context, AFUNPTR orgFuncptr, void * arg0 );


/* ===================================================================== */
/* Commandline Switches */
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


/* ===================================================================== */
// Called every time a new image is loaded.
// Look for routines that we want to replace.
VOID ImageLoad(IMG img, VOID *v)
{
    RTN freeRtn = RTN_FindByName(img, "free");
    if (RTN_Valid(freeRtn))
    {
        PROTO proto_free = PROTO_Allocate( PIN_PARG(void), CALLINGSTD_DEFAULT,
                                           "free", PIN_PARG(void *), PIN_PARG_END() );
        
        RTN_ReplaceSignature(
            freeRtn, AFUNPTR( Jit_Free_IA32 ),
            IARG_PROTOTYPE, proto_free,
            IARG_CONTEXT,
            IARG_ORIG_FUNCPTR,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
            IARG_END);

        cout << "Replaced free() in:"  << IMG_Name(img) << endl;
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

    IMG_AddInstrumentFunction(ImageLoad, 0);
    
    
    PIN_StartProgram();
    
    return 0;
}


/* ===================================================================== */

VOID Jit_Free_IA32( CONTEXT * context, AFUNPTR orgFuncptr, void * ptr)
{
    PIN_CallApplicationFunction( context, PIN_ThreadId(),
                                 CALLINGSTD_DEFAULT, orgFuncptr, NULL,
                                 PIN_PARG(void),
                                 PIN_PARG(void *), ptr,
                                 PIN_PARG_END() );

    cout << "free(" << hex << ptr << ")" << dec << endl;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
