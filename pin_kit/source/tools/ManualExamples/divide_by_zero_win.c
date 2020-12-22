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

#include <Windows.h>
#include <stdio.h>
#define EXPORT_SYM __declspec( dllexport ) 

// divide by zero exception
int DivideByZero()
{
    volatile unsigned int zero;
    unsigned int i;
    __try 
    { 
        fprintf(stderr, "Going to divide by zero\n");
        fflush(stderr);
        zero = 0;
        i  = 1 / zero;
        return 0;
    } 
    __except(GetExceptionCode() == EXCEPTION_INT_DIVIDE_BY_ZERO ? EXCEPTION_EXECUTE_HANDLER : 
        EXCEPTION_CONTINUE_SEARCH)
    { 
        fprintf(stderr, "Catching divide by zero\n");
        fflush(stderr);
        return 1;
    }
    return 0;
}

int main()
{
    if (DivideByZero() != 1)
    {
        exit (-1);
    }
    return 0;
}