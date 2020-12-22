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
 * This test verifies that Pin can emulate a weird signal.
 * The application sends itself an asynchronous signal, but
 * uses a signal number that is normally a synchronous signal.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void Handle(int, siginfo_t *, void *);


int main()
{
    struct sigaction act;
    act.sa_sigaction = Handle;
    act.sa_flags = SA_SIGINFO;
    sigemptyset(&act.sa_mask);
    if (sigaction(SIGFPE, &act, 0) != 0)
    {
        printf("Unable to set up FPE handler\n");
        return 1;
    }

    kill(getpid(), SIGFPE);
    /* should not return */

    printf("Should not return from signal handler\n");
    return 1;
}

static void Handle(int sig, siginfo_t *info, void *ctxt)
{
    if (sig != SIGFPE)
    {
        printf("Got unexpected signal %d\n", sig);
        exit(1);
    }
    if (info->si_code != 0)
    {
        printf("Expected si_code to be zero, but got %d\n", (int)info->si_code);
        exit(1);
    }
    exit(0);
}
