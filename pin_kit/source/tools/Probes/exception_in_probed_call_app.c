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
  This application causes exception in indirect call instruction and catches it in caller.
  The call instruction is located in code region being replaced by Pin probe.
  Pin translation should not affect propagation of the exception to the exception handler.
*/

#include <windows.h>
#include <stdio.h>


static int (*pBar)() = 0;

int bar()
{
    return 0;
}

__declspec(dllexport)
int foo()
{
    // May cause exception due to NULL pointer
    return pBar();
}

int main()
{
    int i;

    __try
    {
        i = foo();
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        // If Pin translated probed code properly, exception will reach the handler
        printf("Exception %08X\n", (unsigned long) GetExceptionCode());
    }

    pBar = bar;

    __try
    {
        i = foo();
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        // No exception expected
        printf("Exception %08X\n", (unsigned long) GetExceptionCode());
    }

    return i;
}
