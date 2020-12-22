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
 *  Print data on each SEC.
 */

#include <iostream>
#include <fstream>
#include "pin.H"
using std::ofstream;
using std::string;
using std::endl;

ofstream out;

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "sec.out", "specify output file name");

VOID ImageLoad(IMG img, VOID * v)
{
    out << "Tool loading " << IMG_Name(img) << " at " << IMG_LoadOffset(img) << endl;
    for (SEC sec = IMG_SecHead(img); SEC_Valid(sec); sec = SEC_Next(sec))
    {
        out << "  sec " << SEC_Name(sec) << " " << SEC_Address(sec) << ":" << SEC_Size(sec) << endl;
        string pos(" ");
        string neg(" not ");
        out << "  This sec is" << (SEC_IsReadable(sec) ? pos : neg) << "readable, ";
        out << "is" << (SEC_IsWriteable(sec) ? pos : neg) << "writeable, ";
        out << "is" << (SEC_IsExecutable(sec) ? pos : neg) << "executable, ";
        out << "and is" << (SEC_Mapped(sec) ? pos : neg) << "mapped." << endl;
    }
}

int main(INT32 argc, CHAR **argv)
{
    out.open(KnobOutputFile.Value().c_str());
    
    PIN_InitSymbols();
    PIN_Init(argc, argv);
    
    IMG_AddInstrumentFunction(ImageLoad, 0);
    
    // Never returns
    PIN_StartProgram();
    
    return 0;
}
