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

#include "pin.H"
#include <iostream>
using std::cout;
using std::endl;

/* ===================================================================== */

BOOL MyPinAttached()
{
    return TRUE;
}

/* ===================================================================== */

VOID ImageLoad(IMG img, VOID *v)
{
    RTN rtn = RTN_FindByName(img, "PinAttached");
    if (RTN_Valid(rtn))
    {
        RTN_Replace(rtn, (AFUNPTR)MyPinAttached);
    }

    if (IMG_IsMainExecutable(img) || IMG_IsVDSO(img))
    {
        return;
    }

    //If str dosn't include "/" then str.substr(idx + 1) returns full str.
    INT idx = IMG_Name(img).find_last_of("/");
    cout << IMG_Name(img).substr(idx + 1) << endl;
}

/* ===================================================================== */

int main(int argc, CHAR *argv[])
{
    PIN_InitSymbols();
    PIN_Init(argc,argv);

    IMG_AddInstrumentFunction(ImageLoad, NULL);

    PIN_StartProgram();

    return 1;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
