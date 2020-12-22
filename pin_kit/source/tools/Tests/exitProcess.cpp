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
 *  Demonstrate the usability of PIN_ExitProcess interface.
 */

#include <signal.h>
#include "pin_tests_util.H"

VOID gotSignal(THREADID threadIndex, CONTEXT_CHANGE_REASON reason, const CONTEXT *from,
               CONTEXT *to, INT32 info, VOID *v)
{
    if (info == SIGUSR1) {
        // the app is in an infinite loop at its exit
        PIN_ExitProcess(0);
    }
}

int main(INT32 argc, CHAR **argv)
{
    PIN_Init(argc, argv);

    PIN_AddContextChangeFunction(gotSignal, 0);

    // Never returns
    PIN_StartProgram();
    
    return 0;
}
