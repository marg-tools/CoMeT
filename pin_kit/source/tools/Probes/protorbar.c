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

// This little application tests recursive calls in probes mode.
//
#include <stdio.h>
static done = 0;


void Bar( int a, int b, int c, int d )
{
    if ( done == 0 )
    {
        done = 1;
        Bar(a+20, b+20, c+20, d+20);
    }
    
    printf( "Bar: %d, %d, %d, %d\n", a,b,c,d );
}
