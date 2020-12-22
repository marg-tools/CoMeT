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
 * This test verifies that Pin correctly delivers a signal during a blocking system call.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

unsigned SigCount = 0;

static void Handle(int);


int main()
{
    struct sigaction sigact;
    ssize_t sz;
    char buf;


    sigact.sa_handler = Handle;
    sigact.sa_flags = 0;
    sigemptyset(&sigact.sa_mask);
    if (sigaction(SIGALRM, &sigact, 0) == -1)
    {
        fprintf(stderr, "Unable to set up handler\n");
        return 1;
    }

    for (;;)
    {
        alarm(3);
        pause();
    }

    printf("Shouldn't get here!!\n");
    return 1;
}

static void Handle(int sig)
{
    printf("Got SIGALRM\n");
    SigCount++;
    if (SigCount > 1)
        exit(0);
}
