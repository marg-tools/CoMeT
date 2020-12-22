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
#include <stdio.h>
#include <unistd.h>

/* ===================================================================== */
/* Command line Switches */
/* ===================================================================== */


BOOL FollowChild(CHILD_PROCESS childProcess, VOID * userData)
{
    fprintf(stdout, "before child:%u\n", getpid());
    return TRUE;
}        

/* ===================================================================== */

int main(INT32 argc, CHAR **argv)
{
    PIN_Init(argc, argv);

    PIN_AddFollowChildProcessFunction(FollowChild, 0);

    PIN_StartProgram();

    return 0;
}

