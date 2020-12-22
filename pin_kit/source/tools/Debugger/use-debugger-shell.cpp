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
 * This is a test of the "debugger-shell" tool extension.  See
 * "InstLib/debugger-shell.H" for a description of the functionality.
 */

#include "debugger-shell.H"

int main(int argc, char **argv)
{
    if (PIN_Init(argc,argv))
        return 1;

    DEBUGGER_SHELL::ISHELL *shell = DEBUGGER_SHELL::CreateShell();
    DEBUGGER_SHELL::STARTUP_ARGUMENTS args;
    args._enableIcountBreakpoints = TRUE;
    if (!shell->Enable(args))
        return 1;

    PIN_StartProgram();
}
