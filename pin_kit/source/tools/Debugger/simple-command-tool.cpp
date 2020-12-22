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
 * Simple tool to test extended commands.
 */

#include <iostream>
#include "pin.H"

bool GotPinCommand = false;
bool GotOurCommand = false;

static bool OnCommand(THREADID, CONTEXT *, const std::string &, std::string *, VOID *);
static void OnExit(INT32, VOID *);


int main(int argc, char * argv[])
{
    PIN_Init(argc, argv);

    PIN_AddDebugInterpreter(OnCommand, 0);
    PIN_AddFiniFunction(OnExit, 0);
    PIN_StartProgram();
    return 0;
}


static bool OnCommand(THREADID, CONTEXT *, const std::string &cmd, std::string *reply, VOID *)
{
    if (cmd == "pin foo")
    {
        // Pin Reserves all command that start with "pin ", so the tool should never see this.
        //
        std::cerr << "Did not expect \"pin\" command\n";
        GotPinCommand = true;
        return true;
    }
    if (cmd == "mycommand")
    {
        *reply = "Got mycommand\n";
        GotOurCommand = true;
        return true;
    }
    return false;
}

static void OnExit(INT32, VOID *)
{
    if (!GotOurCommand)
    {
        std::cerr << "Did not receive \"mycommand\"\n";
        PIN_ExitProcess(1);
    }
    if (GotPinCommand)
    {
        PIN_ExitProcess(1);
    }
}
