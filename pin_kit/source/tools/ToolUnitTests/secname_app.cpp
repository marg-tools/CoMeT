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

#pragma data_seg("dsec")

static char greeting[] = "Hello";

#pragma code_seg("asection")

void report()
{
    printf("%s, world\n", greeting);
}

#pragma code_seg(".text")

int main ()
{
    report();
    return 0;
}
