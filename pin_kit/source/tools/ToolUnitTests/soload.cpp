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

#include <iostream>
#include <fstream>
#include "pin.H"
using std::ofstream;
using std::string;
using std::endl;

#ifdef TARGET_MAC
#define ONE "one.dylib"
#define TWO "two.dylib"
#else
#define ONE "one.so"
#define TWO "two.so"
#endif


ofstream out("soload.out");

VOID ImageLoad(IMG img, VOID * v)
{
    if (IMG_Name(img).find(ONE) != string::npos)
        out << "Loading one.so" << endl;
    if (IMG_Name(img).find(TWO) != string::npos)
        out << "Loading two.so" << endl;
}

VOID ImageUnload(IMG img, VOID * v)
{
    if (IMG_Name(img).find(ONE) != string::npos)
        out << "unloading one.so" << endl;
    if (IMG_Name(img).find(TWO) != string::npos)
        out << "unloading two.so" << endl;
}


int main(INT32 argc, CHAR **argv)
{
    PIN_InitSymbols();

    PIN_Init(argc, argv);
    
    IMG_AddInstrumentFunction(ImageLoad, 0);
    IMG_AddUnloadFunction(ImageUnload, 0);
    
    // Never returns
    PIN_StartProgram();
    
    return 0;
}
