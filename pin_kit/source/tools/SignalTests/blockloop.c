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
 * This test verifies that a tool can intercept a signal that the application
 * blocks.  The application blocks all signals and the tool verifies that it
 * can still receive its intercepted signal.
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    sigset_t mask;

    sigfillset(&mask);
    sigdelset(&mask, SIGALRM);
    sigprocmask(SIG_SETMASK, &mask, 0);
    printf("Signals are blocked\n");
    fflush(stdout);

    alarm(60);  /* kills the process if the test hangs for some reason*/

    for (;;);
    return 0;
}
