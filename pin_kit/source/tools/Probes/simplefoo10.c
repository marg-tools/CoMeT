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
 
EXPORT_SYM int Bar10( int,int,int,int,int,int,int,int,int,int );
 
int main()
{
    int total;

    total = Bar10( 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 );

    printf( "main: total = %d\n", total );
 
    return 0;
}
