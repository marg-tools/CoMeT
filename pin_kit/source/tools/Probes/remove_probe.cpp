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
  Pin does not support an API that removes a probe.  Probes are automatically
  removed when an image is unloaded.  Pin will display the address of the
  probes that are removed if the test is run with
  -xyzzy -mesgon log_probe
*/

/* ===================================================================== */
#include "pin.H"
#include <iostream>
#include <stdlib.h>
#include "tool_macros.h"



/* ===================================================================== */
/* Replacement routines */
/* ===================================================================== */

VOID One_IA32( AFUNPTR orgFuncptr )
{
    orgFuncptr();
    return;
}

VOID One_IA32_2( AFUNPTR orgFuncptr )
{
    orgFuncptr();
    return;
}

/* ===================================================================== */
/* Instrumentation routines */
/* ===================================================================== */

VOID Sanity(IMG img, RTN rtn)
{
    if ( PIN_IsProbeMode() && ! RTN_IsSafeForProbedReplacement( rtn ) )
    {
        LOG( "Cannot replace " + RTN_Name(rtn) + " in " + IMG_Name(img) + "\n" );
        exit(1);
    }
}


/* ===================================================================== */

VOID ReplaceProbed( RTN rtn, PROTO proto)
{
    RTN_ReplaceSignatureProbed(
        rtn, AFUNPTR( One_IA32 ),
        IARG_PROTOTYPE, proto,
        IARG_ORIG_FUNCPTR,
        IARG_END);
    RTN_ReplaceSignatureProbed(
        rtn, AFUNPTR( One_IA32_2 ),
        IARG_PROTOTYPE, proto,
        IARG_ORIG_FUNCPTR,
        IARG_END);
}


/* ===================================================================== */
    
VOID ImageLoad(IMG img, VOID *v)
{
    CONSOLE( "Loading " + IMG_Name(img) + "\n" );
    PROTO proto = PROTO_Allocate( PIN_PARG(void), CALLINGSTD_DEFAULT,
                                  "one", PIN_PARG_END() );
    
    RTN rtn = RTN_FindByName(img, C_MANGLE("one"));
    if (RTN_Valid(rtn))
    {
        Sanity(img, rtn);
        
        LOG( "Replacing one in " + IMG_Name(img) + "\n" );
        LOG( "Address = " + hexstr( RTN_Address(rtn)) + "\n" );
        
        ReplaceProbed(rtn, proto);
    }
    
    PROTO_Free( proto );
}

/* ===================================================================== */

VOID ImageUnload(IMG img, VOID *v)
{
    LOG( "Unloading " + IMG_Name(img) + "\n" ); 
}


/* ===================================================================== */

int main(INT32 argc, CHAR *argv[])
{
    PIN_InitSymbols();
    
    PIN_Init(argc, argv);
    
    IMG_AddInstrumentFunction(ImageLoad, 0);
    IMG_AddUnloadFunction(ImageUnload, 0);
    
    PIN_StartProgramProbed();
    
    return 0;
}


/* ===================================================================== */
/* eof */
/* ===================================================================== */
