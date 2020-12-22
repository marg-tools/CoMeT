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
 * This application is meant to be run with the Pin tool "call-app-stress-tool.cpp".
 * It is a stress test for calling PIN_CallApplicationFunction() while handling signals.
 */

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

extern "C" void PIN_TEST_FOO();
extern "C" void PIN_TEST_BAR();
static void Handle(int);

typedef void (*FUN)();

static const unsigned SIGCOUNT = 1000;

volatile FUN pFoo = PIN_TEST_FOO;
volatile unsigned SigCount = 0;
volatile unsigned long LoopCount = 0;


int main()
{
    struct sigaction act;
    act.sa_handler = Handle;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    if (sigaction(SIGALRM, &act, 0) != 0)
    {
        fprintf(stderr, "Unable to set ALRM handler\n");
        return 1;
    }

    struct itimerval itval;
    itval.it_interval.tv_sec = 0;
    itval.it_interval.tv_usec = 10000;
    itval.it_value.tv_sec = 0;
    itval.it_value.tv_usec = 10000;
    if (setitimer(ITIMER_REAL, &itval, 0) == -1)
    {
        fprintf(stderr, "Unable to set up timer\n");
        return 1;
    }

    // Each iteration of this loop causes the Pin tool to execute a PIN_CallApplicationFunction().
    //
    while (SigCount < SIGCOUNT)
    {
        pFoo();
        LoopCount++;
    }

    itval.it_value.tv_sec = 0;
    itval.it_value.tv_usec = 0;
    if (setitimer(ITIMER_REAL, &itval, 0) == -1)
    {
        fprintf(stderr, "Unable to disable timer\n");
        return 1;
    }

    printf("Main returning\n");
    return 0;
}


void PIN_TEST_FOO()
{
    // The Pin tool places an instrumentation point here, which calls PIN_TEST_BAR().
}


void PIN_TEST_BAR()
{
}


static void Handle(int sig)
{
    SigCount++;
    printf("SigCount=%u, LoopCount=%lu\n", SigCount, LoopCount);
    fflush(stdout);
}
