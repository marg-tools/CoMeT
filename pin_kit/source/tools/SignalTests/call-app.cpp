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
 * This application is meant to be run with the Pin tool "call-app-tool.cpp".
 */

#include <stdio.h>
#include <signal.h>

extern "C" void PIN_TEST_FOO();
extern "C" void PIN_TEST_BAR();
static void Handle(int);

typedef void (*FUN)();
volatile FUN pFoo = PIN_TEST_FOO;


int main()
{
    struct sigaction act;
    act.sa_handler = Handle;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    if (sigaction(SIGUSR1, &act, 0) != 0)
    {
        fprintf(stderr, "Unable to set USR1 handler\n");
        return 1;
    }

    // Call through a function pointer to prevent the compiler from in-lining.
    //
    pFoo();

    printf("Main returning\n");
    return 0;
}


void PIN_TEST_FOO()
{
    // The Pin tool places an instrumentation point here, which calls PIN_TEST_BAR().

    printf("Calling Foo\n");
}


void PIN_TEST_BAR()
{
    printf("Calling Bar\n");
}


static void Handle(int sig)
{
    if (sig == SIGUSR1)
        printf("Got SIGUSR1\n");
    else
        printf("Got unexpected signal %d\n", sig);
}
