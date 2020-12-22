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
#include <syscall.h>
#include <unistd.h>
#include <errno.h>

/*! @file
 *
 * This test checks that the emulation of arch_prctl calls the
 * native syscall when it is not a known sub-function
 */

int main()
{
    const int func = 0x3000;
    long arg = 0;
    void *ptr = &arg;
    int res = syscall(__NR_arch_prctl, func, ptr);

    printf("Syscall return: %d\n", res);

    if (res != -1)
        return 1;

    return 0;
}

