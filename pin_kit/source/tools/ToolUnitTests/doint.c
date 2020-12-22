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


static void SetupSigHandler();
static void Handle(int);
extern void DoInt();


int main()
{
    SetupSigHandler();
    DoInt();
    return 0;
}


static void SetupSigHandler()
{
    struct sigaction act;

    act.sa_handler = Handle;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGSEGV, &act, 0);
    sigaction(SIGILL, &act, 0);
}

static void Handle(int sig)
{
    printf("Got signal %d\n", sig);
    exit(0);
}
