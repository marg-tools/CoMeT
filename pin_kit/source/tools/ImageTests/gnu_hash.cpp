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
using std::cerr;
using std::string;
using std::endl;

/* ===================================================================== */

/*!
 * Print out the error message and exit the process.
 */
 VOID AbortProcess(const string & msg, unsigned long code)
{
    cerr << "Test aborted: " << msg << " with code " << code << endl;
    PIN_WriteErrorMessage(msg.c_str(), 1002, PIN_ERR_FATAL, 0);
    PIN_ExitProcess(1);
}

UINT appSecCount = 0;
UINT secCount = 0;

VOID GetSectionCount(ADDRINT count)
{
    appSecCount = count;
}

/* ===================================================================== */
VOID ImageLoad(IMG img, VOID *v)
{
    if (IMG_IsMainExecutable(img))
    {
        BOOL gnuFound = FALSE;
        for(SEC sec = IMG_SecHead(img); SEC_Valid(sec); sec = SEC_Next(sec))
        {
            if (".gnu.hash" == SEC_Name(sec))
            {
                gnuFound = TRUE;
                cout << ".gnu.hash was found" << endl;
            }
            ++secCount;
        }

        if (!gnuFound)
        {
            AbortProcess(".gnu.hash wasn't found!!", 0);
        }

        RTN rtn = RTN_FindByName(img, "TellPinSectionCount");

        if (RTN_Valid(rtn))
        {
            RTN_Open(rtn);
            RTN_InsertCall(rtn, IPOINT_BEFORE, AFUNPTR(GetSectionCount),
                IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                IARG_END);
            RTN_Close(rtn);
        }
        else
        {
            AbortProcess("TellPinSectionCount wasn't found!!", 0);
        }
    }
}

VOID Fini(INT32 code, VOID *v)
{
    if (appSecCount != secCount)
    {
        AbortProcess("PIN stores different number of sections than Number of section headers!", 0);
    }
}

/* ===================================================================== */

int main(int argc, CHAR *argv[])
{
    PIN_InitSymbols();
    PIN_Init(argc,argv);

    IMG_AddInstrumentFunction(ImageLoad, NULL);

    PIN_AddFiniFunction(Fini, NULL);

    PIN_StartProgram();

    return 1;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
