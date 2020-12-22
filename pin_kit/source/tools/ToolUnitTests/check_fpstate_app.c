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

void trap_me() 
{
    printf("In trap me function\n");
}

int main()
{
    /* want to setup the mxcsr exception bits */
    double a, b, c, d;
    unsigned long long cc;

    a = 1;
    b = 3;
    c = 0;

    d = a / b;
    c = 1 / c;
    
    trap_me();
    
    cc = *(unsigned long long*)&c;
    printf("d: %.6f c: 0x%llx\n", d, cc);

    return 0;
}
