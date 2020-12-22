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
  Replace an original function with a custom function defined in the tool. The
  new function can have either the same or different signature from that of its
  original function.
*/

/* ===================================================================== */
#include "pin.H"
#include <iostream>
using std::dec;
using std::hex;
using std::cout;
using std::endl;


/* ===================================================================== */
static void * (*pf_bar)(long, long);

/* ===================================================================== */
void * Boo(  CONTEXT * ctxt, AFUNPTR origPtr, long one, long two )
{
    cout << "Jitting Bar4() with return value" << endl;
    cout << "bar4 origptr = " << hex << (long)origPtr << dec << endl;

    void * res;
    
    PIN_CallApplicationFunction( ctxt, PIN_ThreadId(),
                                 CALLINGSTD_DEFAULT, origPtr, NULL,
                                 PIN_PARG(void *), &res,
                                 PIN_PARG(long), one,
                                 PIN_PARG(long), two,
                                 PIN_PARG_END() );
    
    cout << "Returned from Bar4(); res = " << hex << (long)res << dec << endl;

    return res;
}


/* ===================================================================== */
VOID ImageLoad(IMG img, VOID *v)
{
    cout << IMG_Name(img) << endl;

    
    PROTO proto = PROTO_Allocate( PIN_PARG(void *), CALLINGSTD_DEFAULT,
                                  "Bar4", PIN_PARG(long), PIN_PARG(long),
                                  PIN_PARG_END() );
    
    RTN rtn = RTN_FindByName(img, "Bar4");
    if (RTN_Valid(rtn))
    {
        cout << "Replacing " << RTN_Name(rtn) << " in " << IMG_Name(img) << endl;

        pf_bar = (void * (*)(long, long))RTN_ReplaceSignature(
            rtn, AFUNPTR(Boo),
            IARG_PROTOTYPE, proto,
            IARG_CONTEXT,
            IARG_ORIG_FUNCPTR,
            IARG_ADDRINT, 1,
            IARG_ADDRINT, 2,
            IARG_END);
        cout << "pf_bar = " << hex << (long)pf_bar << dec << endl;

    }    
    PROTO_Free( proto );
}

/* ===================================================================== */
int main(INT32 argc, CHAR *argv[])
{
    PIN_InitSymbols();

    PIN_Init(argc, argv);

    IMG_AddInstrumentFunction(ImageLoad, 0);
    
    PIN_StartProgram();

    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */

