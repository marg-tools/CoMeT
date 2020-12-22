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
  This is a negative test.
*/

/* ===================================================================== */
#include "pin.H"
#include <iostream>
using std::endl;
using std::string;
using std::cout;


/* ===================================================================== */
VOID ImageLoad(IMG img, VOID *v)
{
    if ( IMG_IsMainExecutable( img ))
    {
        string s = "0.001";
        FLT64 f = FLT64FromString( s );
        cout << s << "=" << f << endl;

        s = "-0.1e-2";
        f = FLT64FromString( s );
        cout << s << "=" << f << endl;

        s = "100.";
        f = FLT64FromString( s );
        cout << s << "=" << f << endl;

        s = "1.0E2";
        f = FLT64FromString( s );
        cout << s << "=" << f << endl;

        s = "+1";
        f = FLT64FromString( s );
        cout << s << "=" << f << endl;

        // this should report an error
        s = "1.00.00";
        f = FLT64FromString( s );
        cout << s << "=" << f << endl;
    }
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
