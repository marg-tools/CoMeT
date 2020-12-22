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

//
// This tool demonstrates how to get the value of the application's
// error code on windows in probe mode.
//

#include "pin.H"
#include <iostream>
#include <stdlib.h>
#include <errno.h>


using std::cerr;
using std::endl;

namespace WINDOWS
{
    #include <windows.h>
}

typedef ADDRINT (*GET_LAST_ERROR_FUNPTR)();

// Address of the GetLastError API.
ADDRINT pfnGetLastError = 0; 


/* ===================================================================== */
VOID ToolCheckError()
{
    if ( pfnGetLastError != 0 )
    {
        ADDRINT err_code = (*(GET_LAST_ERROR_FUNPTR)pfnGetLastError)();
        
        cerr << "Tool: error code=" << err_code << endl;
    }
    else
        cerr << "Tool: GetLastError() not found." << endl;
    
}

/* ===================================================================== */
VOID ImageLoad(IMG img, VOID *v)
{
    if ( IMG_IsMainExecutable( img ))
    {
        PROTO proto = PROTO_Allocate( PIN_PARG(void), CALLINGSTD_DEFAULT,
                                      "CheckError", PIN_PARG_END() );
        
        RTN rtn = RTN_FindByName(img, "CheckError");
        if (RTN_Valid(rtn))
        {
            RTN_ReplaceSignatureProbed(rtn, AFUNPTR(ToolCheckError),
                                       IARG_PROTOTYPE, proto,
                                       IARG_END);
        }    
        PROTO_Free( proto );
    }
}

/* ===================================================================== */
int main(INT32 argc, CHAR *argv[])
{
    pfnGetLastError = (ADDRINT)WINDOWS::GetProcAddress(
                               WINDOWS::GetModuleHandle("kernel32.dll"), "GetLastError");
    PIN_InitSymbols();

    PIN_Init(argc, argv);

    IMG_AddInstrumentFunction(ImageLoad, 0);
    
    PIN_StartProgramProbed();

    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */


