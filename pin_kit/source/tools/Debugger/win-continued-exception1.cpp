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

#include <windows.h>
#include <stdio.h>

static BOOL SafeDiv(INT32, INT32, INT32 *);
static int MyFilter(unsigned long);


int main()
{
    INT32 res;
    if (!SafeDiv(10, 0, &res))
    {
        printf("Divide by zero!\n");
        fflush(stdout);
    }
    return 0;
}

static BOOL SafeDiv(INT32 dividend, INT32 divisor, INT32 *pResult)
{
    __try 
    { 
        *pResult = dividend / divisor; 
    } 
    __except(MyFilter(GetExceptionCode()))
    { 
        return FALSE;
    }
    return TRUE;
} 

static int MyFilter(unsigned long code)
{
    return EXCEPTION_CONTINUE_SEARCH;
}
