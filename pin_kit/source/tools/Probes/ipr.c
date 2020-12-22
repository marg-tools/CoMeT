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

#include <stdio.h>
static int a=0;

void iprel_imm()
{
    a = 1;
}

void iprel_reg(int b)
{
    a = b;
}

int reg_iprel()
{
    return a;
}

int main()
{
    int c;
    
    iprel_imm();
    printf( "a should be 1; a = %d\n", a);
    
    iprel_reg(2);
    printf( "a should be 2; a = %d\n", a);

    c = reg_iprel();
    printf( "c should be 2; c = %d\n", c);
    return 0;
}
