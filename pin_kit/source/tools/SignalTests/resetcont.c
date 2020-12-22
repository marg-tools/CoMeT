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

#include <signal.h>
#include <stdio.h>


void handle(int);


int main()
{
    struct sigaction sigact;

    sigact.sa_handler = handle;
    sigact.sa_flags = SA_RESETHAND;
    sigemptyset(&sigact.sa_mask);
    if (sigaction(SIGCONT, &sigact, 0) == -1)
    {
        printf("Unable to handle signal\n");
        return 1;
    }

    raise(SIGCONT);
    raise(SIGCONT);

    printf("Exiting after second SIGCONT\n");
    return 0;
}

void handle(int sig)
{
    if (sig == SIGCONT)
        printf("Got signal CONT\n");
    else
        printf("Got signal %d\n", sig);
    fflush(stdout);
}
