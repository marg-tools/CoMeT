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
#include <stdlib.h>
#include <signal.h>

static void Handle(int);
static void HandlerIsEstablished();

typedef void (*PF)();
volatile PF pfEstablished;


int main()
{
    struct sigaction act;

    act.sa_handler = Handle;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    if (sigaction(SIGUSR1, &act, 0) != 0)
    {
        fprintf(stderr, "Unable to set up USR1 handler\n");
        return 1;
    }

    pfEstablished = HandlerIsEstablished;
    pfEstablished();

    raise(SIGUSR1);
    raise(SIGUSR1);

    fprintf(stderr, "Should exit from handler\n");
    return 1;
}


static void Handle(int sig)
{
    static int Count = 0;

    printf("In handler\n");
    if (++Count == 2)
        exit(0);
}


static void HandlerIsEstablished()
{
    /*
     * Pin can add an instrumentation point here to be notified
     * when the signal handler is established.
     */
}
