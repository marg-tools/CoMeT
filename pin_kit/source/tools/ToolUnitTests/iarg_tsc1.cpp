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

// This tool test RTN_InsHead RTN_InsHeadOnly and RTN_InsertCall (before)


#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "pin.H"
using std::ofstream;
using std::hex;
using std::endl;

ofstream OutFile;


VOID AtRtn1(VOID* name, UINT64 tsc)
{
	OutFile << std::left << std::setw(32) << reinterpret_cast<CHAR *>(name) << "," << hex << tsc << endl;
}

VOID PIN_FAST_ANALYSIS_CALL AtRtn2(VOID* name, UINT64 tsc)
{
    OutFile << std::left << std::setw(32) << reinterpret_cast<CHAR *>(name) << "," << hex << tsc << endl;
}


VOID Image(IMG img, void *v)
{
    for (SEC sec = IMG_SecHead(img); SEC_Valid(sec); sec = SEC_Next(sec))
    {
        for (RTN rtn = SEC_RtnHead(sec); RTN_Valid(rtn); rtn = RTN_Next(rtn))
        {
            RTN_Open(rtn);

            RTN_InsertCall( rtn, IPOINT_BEFORE, AFUNPTR(AtRtn1),  IARG_PTR, RTN_Name(rtn).c_str(), IARG_TSC , IARG_END);
            RTN_InsertCall( rtn, IPOINT_BEFORE, AFUNPTR(AtRtn2), IARG_FAST_ANALYSIS_CALL, IARG_PTR, RTN_Name(rtn).c_str(), IARG_TSC , IARG_END);

            RTN_Close(rtn);
        }
    }
}

VOID Fini (INT32 code, VOID *v)
{
    OutFile.close();
}

int main(int argc, char **argv)
{
    PIN_Init(argc, argv);
    PIN_InitSymbols();

    OutFile.open("iarg_tsc1.out");

    IMG_AddInstrumentFunction(Image, 0);
    PIN_AddFiniFunction(Fini, 0);

    PIN_StartProgram();
    return 0;
}
