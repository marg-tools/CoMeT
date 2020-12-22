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
   Demonstrate a way for a tool to present a stack walk when a tool calls
   nested replaced functions.
*/

/* ===================================================================== */
#include "pin.H"
#include <iostream>
#include <stdlib.h>
#include "tool_macros.h"
using std::endl;
using std::dec;
using std::hex;
using std::string;
using std::cout;


/* ===================================================================== */
/* Globals */ 
/* ===================================================================== */

typedef VOID (*FUNCPTR)(ADDRINT arg);

ADDRINT relocated_address[3];


/* ===================================================================== */
/* Replacement routines  */
/* ===================================================================== */

VOID First( FUNCPTR fp, CONTEXT * ctxt, ADDRINT arg )
{
    (*fp)(arg);
}

VOID Second( FUNCPTR fp, CONTEXT * ctxt, ADDRINT arg )
{
    (*fp)(arg);
}

VOID Third( FUNCPTR fp, CONTEXT * ctxt, ADDRINT arg )
{
    (*fp)(arg);
}


/* ===================================================================== */
/* Instrumentation Routines  */
/* ===================================================================== */

void Replace( IMG img, string name, AFUNPTR funptr, int index )
{
    RTN rtn = RTN_FindByName(img, name.c_str());

    if (RTN_Valid(rtn))
    {
        if ( RTN_IsSafeForProbedReplacement( rtn ) )
        {
            PROTO proto = PROTO_Allocate( PIN_PARG(void),
                                          CALLINGSTD_DEFAULT, name.c_str(),
                                          PIN_PARG(unsigned long),
                                          PIN_PARG_END() );
            
            relocated_address[index] = (ADDRINT)RTN_ReplaceSignatureProbed( rtn, funptr,
                                        IARG_PROTOTYPE, proto,
                                        IARG_ORIG_FUNCPTR,
                                        IARG_CONTEXT,
                                        IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                                        IARG_END);
            
            PROTO_Free( proto );
        }
    }
}


VOID ImageLoad(IMG img, VOID *v)
{
    if ( ! IMG_IsMainExecutable( img ) )
        return;

    int index=0;
    
    Replace( img, C_MANGLE("first"),  AFUNPTR( First ),  index++ );
    Replace( img, C_MANGLE("second"), AFUNPTR( Second ), index++ );
    Replace( img, C_MANGLE("third"),  AFUNPTR( Third ),  index++ );
}


BOOL Report( IMG img, string name, int index )
{
    BOOL success = FALSE;
    PIN_CODE_RANGE * ranges=0;
    
    RTN rtn = RTN_FindByName(img, name.c_str());
    if (RTN_Valid(rtn))
    {
        INT32 num = RTN_CodeRangesProbed( rtn, 0, ranges );
        
        INT32 rsize = num * sizeof(PIN_CODE_RANGE);
        
        ranges = reinterpret_cast< PIN_CODE_RANGE * >( malloc( rsize ));

        INT32 count = RTN_CodeRangesProbed( rtn, num, ranges );

        if ( num != count)
            cout << "Error: wrong size returned!" << endl;
        
        cout << "rtn   start address   size" << endl;
        for ( int i=0; i<num; i++ )
        {
            cout << " " << RTN_Id(rtn) << "       " << hex <<
                ranges[i].start_address << "        " <<
                ranges[i].size << dec << endl;
        }
        cout << endl;

        if ( relocated_address[index] == ranges[0].start_address )
            success = TRUE;
        
        free ( ranges );
    }
    return success;
}


VOID ProbesInserted( IMG img, VOID *v )
{ 
    if ( ! IMG_IsMainExecutable( img ) )
        return;

    int index = 0;
    
    BOOL stat = Report( img, C_MANGLE("first"),  index++ );
    if ( stat == TRUE )
         stat = Report( img, C_MANGLE("second"), index++ );
    if ( stat == TRUE )
         stat = Report( img, C_MANGLE("third"),  index++ );

    if ( stat == TRUE )
        cout << "Success!!" << endl;
    else
        cout << "Error.  Cannot find relocated address." << endl;
}



/* ===================================================================== */
/* Main  */
/* ===================================================================== */

int main(INT32 argc, CHAR *argv[])
{
    PIN_InitSymbols();

    PIN_Init(argc, argv);

    IMG_AddInstrumentFunction(ImageLoad, 0);
    PIN_AddProbesInsertedFunction( ProbesInserted, 0 );
    
    PIN_StartProgramProbed();

    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
    
