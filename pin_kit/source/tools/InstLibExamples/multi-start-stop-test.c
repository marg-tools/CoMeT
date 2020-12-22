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

void foo()
{
   printf("inside foo\n");
}

void mark1()
{
   printf("inside mark1\n");
}

void mark2()
{
   printf("inside mark2\n");
}

void bar()
{
   printf("inside bar \n");
}

int main()
{
    printf("inside main calling foo\n");
    mark1();
    foo();
    printf("inside main calling bar\n");
    mark2();
    bar();
    return 0;
}
