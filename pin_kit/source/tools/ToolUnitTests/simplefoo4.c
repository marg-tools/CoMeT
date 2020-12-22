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

// This little application is used to test calling application functions.
//
#include <stdio.h>

#if defined (TARGET_WINDOWS)
#define EXPORT_SYM __declspec( dllexport ) 
#else
#define EXPORT_SYM extern
#endif

EXPORT_SYM void * Bar4( long one, long two );

int main()
{
    void * res;
    
    res = Bar4(6, 8);

    printf("main: res = %lx\n", (long)res);

    res = Bar4(10, 12);

    printf("main: res = %lx\n", (long)res);

    res = Bar4(14, 16);

    printf("main: res = %lx\n", (long)res);

    return 0;
}
