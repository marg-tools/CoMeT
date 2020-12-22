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

// This little application tests passing arguments in probes mode.
//
#include <stdio.h>

void Bar( int a, int b, int c, int d )
{
    printf( "Bar: %d, %d, %d, %d\n", a,b,c,d );
}

void Baz( int a)
{
    printf( "Baz: %d\n", a);
}
