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
 * A tool that has a custom command that changes the application's
 * register state.  We use this to test the "invalidate registers" API.
 */

#include "pin.H"

static BOOL OnCommand(THREADID, CONTEXT *, const std::string &, std::string *, VOID *);


int main(int argc, char * argv[])
{
    PIN_Init(argc, argv);

    PIN_AddDebugInterpreter(OnCommand, 0);
    PIN_StartProgram();
    return 0;
}

static BOOL OnCommand(THREADID, CONTEXT *ctxt, const std::string &cmd, std::string *reply, VOID *)
{
    if (cmd == "clear-eflags")
    {
        PIN_SetContextReg(ctxt, REG_GFLAGS, 0);
        *reply = "Changed $EFLAGS to 0\n";
        return TRUE;
    }
    return FALSE;
}
