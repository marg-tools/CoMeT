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
// regparms test

#include <stdio.h>

extern int __fastcall FastBar10( int,int,int,int,int,int,int,int,int,int );

int main()
{
	int sum;

    sum = FastBar10(6, 2, 4, 8, 1, 9, 0, 7, 3, 5);

	printf( " main: sum=%d\n", sum );

    return 0;
}
