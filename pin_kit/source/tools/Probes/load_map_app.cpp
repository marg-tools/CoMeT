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

extern "C" void one();

// We will use probe on the following function, so its first BBL
// should be long enough to avoid jumps to our trampoline code, even
// when the compiler uses optimizations.
extern "C" void do_nothing()
{
    int n;
    for (int i=0; i< 100; i++)
    {
        printf(".");
        n++;
    }
    printf("%d\n", n);
}

int main()
{
    do_nothing();
    one();
    printf("Hello, world\n");
    return 0;
}

