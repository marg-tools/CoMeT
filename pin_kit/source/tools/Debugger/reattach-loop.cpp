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

#include <stdio.h>

volatile int MyVariable = 89;
int Iterations = 0;

static void Breakpoint();


int main()
{
    printf("Before the loop, MyVariable = %d\n", MyVariable);

    // The debugger changes 'MyVariable', which causes the loop to drop out.
    //
    while (MyVariable == 89)
    {
        Iterations++;
        Breakpoint();
    }

    printf("After the loop, MyVariable = %d\n", MyVariable);
    return 0;
}

static void Breakpoint()
{
    /* Debugger places a breakpoint here */
}
