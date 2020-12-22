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
static int (*pf_bar)( int, int, int, int, int, int, int, int, int, int );

/* ===================================================================== */
int Boo(  CONTEXT * ctxt, AFUNPTR pf_Bar, int one, int two, int three,
           int four, int five, int six, int seven, int eight, int nine, int zero )
{
    int ret = 0;

    cout << "Jitting Bar10() with ten arguments and one return value." << endl;
    cout << "&ret = " << hex << &ret << dec << endl;
    
    
    PIN_CallApplicationFunction( ctxt, PIN_ThreadId(),
                                 CALLINGSTD_DEFAULT, pf_Bar, NULL,
                                 PIN_PARG(int), &ret,
                                 PIN_PARG(int), one,
                                 PIN_PARG(int), two,
                                 PIN_PARG(int), three,
                                 PIN_PARG(int), four,
                                 PIN_PARG(int), five,
                                 PIN_PARG(int), six,
                                 PIN_PARG(int), seven,
                                 PIN_PARG(int), eight,
                                 PIN_PARG(int), nine,
                                 PIN_PARG(int), zero,
                                 PIN_PARG_END() );
    
    cout << "Returned from Bar10(); ret = " << ret << endl;

    return ret;
}


/* ===================================================================== */
VOID ImageLoad(IMG img, VOID *v)
{
    cout << IMG_Name(img) << endl;

    PROTO proto = PROTO_Allocate( PIN_PARG(int), CALLINGSTD_DEFAULT,
                                  "Bar10", PIN_PARG(int), PIN_PARG(int),
                                  PIN_PARG(int), PIN_PARG(int),
                                  PIN_PARG(int), PIN_PARG(int),
                                  PIN_PARG(int), PIN_PARG(int),
                                  PIN_PARG(int), PIN_PARG(int),
                                  PIN_PARG_END() );
    

    RTN rtn = RTN_FindByName(img, "Bar10");
    if (RTN_Valid(rtn))
    {
        cout << "Replacing " << RTN_Name(rtn) << " in " << IMG_Name(img) << endl;

        pf_bar = (int (*)(int, int, int, int, int, int, int, int, int, int))RTN_ReplaceSignature(
            rtn, AFUNPTR(Boo),
            IARG_PROTOTYPE, proto,
            IARG_CONTEXT,
            IARG_ORIG_FUNCPTR,
            IARG_UINT32, 1,
            IARG_UINT32, 2,
            IARG_UINT32, 3,
            IARG_UINT32, 4,
            IARG_UINT32, 5,
            IARG_UINT32, 6,
            IARG_UINT32, 7,
            IARG_UINT32, 8,
            IARG_UINT32, 9,
            IARG_UINT32, 0,
            IARG_END);

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

