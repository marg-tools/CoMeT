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

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "pin.H"
using std::endl;
using std::flush;
using std::cerr;
using std::string;
using std::cout;


string FILE_TO_FIND= "hello";

void InstImage(IMG img, void *v)
{
    cout << "Image name = " << IMG_Name(img) << endl << flush;

    for (SEC sec = IMG_SecHead(img); SEC_Valid(sec); sec = SEC_Next(sec))
    {
        for (RTN rtn = SEC_RtnHead(sec); RTN_Valid(rtn); rtn = RTN_Next(rtn))
        {
            RTN_Open(rtn);

            for (INS ins = RTN_InsHead(rtn); INS_Valid(ins); ins = INS_Next(ins))
            {
                int lineno;
                string srcfile="";
                PIN_GetSourceLocation(INS_Address(ins), NULL, &lineno, &srcfile);
                if(srcfile.find(FILE_TO_FIND) != srcfile.npos)
                {
                    fprintf(stderr, "passed\n");
                    break;
                }
            }
            RTN_Close(rtn);
        }
    }
}

int main(int argc, char **argv)
{
    PIN_InitSymbols();

    if (PIN_Init(argc, argv))
    {
        cerr << "usage..." << endl;
        return EXIT_FAILURE;
    }

    IMG_AddInstrumentFunction(InstImage, 0);

    PIN_StartProgram();
    return EXIT_FAILURE;
}
