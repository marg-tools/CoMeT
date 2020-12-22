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
 * This tool enables PinADX debugging via PIN_SetDebugMode().  It should be
 * run without -appdebug.
 */
 
#include <iostream>
#include "pin.H"


static void OnThreadStart(THREADID, CONTEXT *, INT32, VOID *);


int main(int argc, char * argv[])
{
    PIN_Init(argc, argv);

    if (PIN_GetDebugStatus() != DEBUG_STATUS_DISABLED)
    {
        std::cerr << "Expected DISABLED status initially" << std::endl;
        return 1;
    }

    DEBUG_MODE mode;
    mode._type = DEBUG_CONNECTION_TYPE_TCP_SERVER;
    mode._options = DEBUG_MODE_OPTION_STOP_AT_ENTRY;
    if (!PIN_SetDebugMode(&mode))
    {
        std::cerr << "Error from PIN_SetDebugMode()" << std::endl;
        return 1;
    }

    if (PIN_GetDebugStatus() != DEBUG_STATUS_UNCONNECTABLE)
    {
        std::cerr << "Expected UNCONNECTABLE status in main" << std::endl;
        return 1;
    }

    PIN_AddThreadStartFunction(OnThreadStart, 0);
    PIN_StartProgram();
    return 0;
}

static void OnThreadStart(THREADID, CONTEXT *, INT32, VOID *)
{
    DEBUG_STATUS status = PIN_GetDebugStatus();
    if (status != DEBUG_STATUS_UNCONNECTED && status != DEBUG_STATUS_CONNECTED)
    {
        std::cerr << "Expected UNCONNECTED / CONNECTED status after application started" << std::endl;
        PIN_ExitProcess(1);
    }

    if (!PIN_WaitForDebuggerToConnect(0))
    {
        std::cerr << "Error from PIN_WaitForDebuggerToConnect()" << std::endl;
        PIN_ExitProcess(1);
    }
}
