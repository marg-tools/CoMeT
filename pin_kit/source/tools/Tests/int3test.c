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

/* TO COMPILE: 
      gcc -o int3test int3test.c 
 */
#include <stdio.h>
#include <stdint.h>

int main(int argc, char** argv)
{
    int y,i,x=1;
    if (argc == 2)
        y = atoi(argv[1]);
    else
        y = 5;
    asm volatile("int3");
    for( i=0;i<10;i++)
        x = x * y;
    printf("%d\n",x);
}
