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
 * Verify that an application crashes if it attempts to handle a SEGV
 * when SEGV is blocked.  Also, verify that Pin is notified that the
 * application terminated.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


static void Handle(int);

int main()
{
    struct sigaction act;
    sigset_t ss;

    act.sa_handler = Handle;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    if (sigaction(SIGSEGV, &act, 0) != 0)
    {
        printf("Unable to set up SEGV handler\n");
        return 1;
    }

    sigemptyset(&ss);
    sigaddset(&ss, SIGSEGV);
    if (sigprocmask(SIG_BLOCK, &ss, 0) != 0)
    {
        printf("Unable to block SEGV\n");
        return 1;
    }

    /*
     * We expect this to crash because SEGV is blocked.
     */
    volatile int *p = (volatile int *)0x9;
    *p = 8;

    return 0;
}

static void Handle(int sig)
{
    /* We do NOT expect this handler to be called */
    printf("Got SEGV\n");
    fflush(stdout);
    exit(1);
}
