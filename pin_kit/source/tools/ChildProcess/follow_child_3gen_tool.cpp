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
*/

#include "pin.H"
#include <iostream>
namespace WIND
{
#include <windows.h>
}

using std::cout;
using std::endl;

WIND::HANDLE outputMutex;


// use mutex to synchronize outputs from multiple instances of this tool
void MutexWriteToStdout (char *msg)
{
    
    WIND::WaitForSingleObject (outputMutex, INFINITE);
    
    printf (msg);
    
    fflush (stdout);
    
    WIND::ReleaseMutex (outputMutex);
}


int main(INT32 argc, CHAR **argv)
{
    outputMutex = WIND::CreateMutex (NULL, false /* not initial owner*/, "pin_child_tool_output_mutex");
    if (outputMutex == NULL)
    {
        cout << "failed to create outputMutex\n";
        exit (0);
    }

    PIN_InitSymbols();
    PIN_Init(argc, argv);
    
    // Never returns
    if ( PIN_IsProbeMode() )
    {
        MutexWriteToStdout ("In follow_child PinTool is probed 1\n");
        PIN_StartProgramProbed();
    }
    else
    {
        MutexWriteToStdout ("In follow_child PinTool is probed 0\n");
        PIN_StartProgram();
    }

    return 0;
}

