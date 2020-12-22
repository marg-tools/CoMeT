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

void Foo(int a, int b, int c);
void Inner(int x);


int main()
{
    printf("This is the main routine\n");
    Foo(1, 2, 3);
    Inner(10);
    return 0;
}


void Foo(int a, int b, int c)
{
    printf("Foo: a=%d, b=%d, c=%d\n", a, b, c);
    Inner(a+b+c);
}

void Inner(int x)
{
    printf("Bar: x=%d\n", x);
    if (x == 10)
        Inner(12);
}
