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
    This application causes exception in system call LeaveCriticalSection and catches it.
    The exception happens in first bytes of the system call's code
    that will be copied and translated when probed.
*/

#include <windows.h>
#include <stdio.h>

int main ( void )
{
    int res = 0;

    __try
    {
        LeaveCriticalSection (NULL);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        printf("Exception %08X\n", (unsigned long) GetExceptionCode());
        fflush(stdout);
 	    res++;
    }

	// Try again, if exceptions aren't handled in the library, we'll have a problem

    __try
    {
        LeaveCriticalSection (NULL);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        printf("Exception %08X\n", (unsigned long) GetExceptionCode());
        fflush(stdout);
        res++;
    }

    return 0;
}
