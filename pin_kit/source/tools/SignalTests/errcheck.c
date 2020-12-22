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

/*
 * This test verifies that Pin correctly emulates the error returns from the
 * various signal related system calls.
 */

#include <stdio.h>
#include <errno.h>
#include <signal.h>


int main()
{
    struct sigaction act;
    sigset_t set;
    stack_t stack;

    errno = 0;
    if (sigaction(0x12345678, &act, 0) != -1 || errno != EINVAL)
    {
        fprintf(stderr, "sigaction: Expected EINVAL, but got %d\n", errno);
        return 1;
    }

    errno = 0;
    if (sigprocmask(0x12345678, &set, 0) != -1 || errno != EINVAL)
    {
        fprintf(stderr, "sigprocmask: Expected EINVAL, but got %d\n", errno);
        return 1;
    }

    errno = 0;
    stack.ss_sp = 0;
    stack.ss_size = 0;
    stack.ss_flags = 0x12345678;
    if (sigaltstack(&stack, 0) != -1 || (errno != EINVAL && errno != ENOMEM))
    {
        fprintf(stderr, "sigaltstack: Expected EINVAL or ENOMEM, but got %d\n", errno);
        return 1;
    }

    return 0;
}
