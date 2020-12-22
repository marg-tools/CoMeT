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

/*
This tool is used to output that the child process was created in the correct mode 
(probe or jit)
It does PIN_InitSymbols
*/
#include "pin.H"
#include <iostream>

using std::cout;
using std::endl;


int main(INT32 argc, CHAR **argv)
{
    PIN_InitSymbols();
    PIN_Init(argc, argv);
    

    cout << "In follow_child with_sym PinTool is probed " << decstr(PIN_IsProbeMode()) << endl;

    // Never returns
    if ( PIN_IsProbeMode() )
    {
        PIN_StartProgramProbed();
    }
    else
    {
        PIN_StartProgram();
    }

    return 0;
}

