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
 * Verifies that handles the application's signal mask correctly even when
 * one signal interrupts another signal's handler.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <signal.h>


static void HandleUSR1(int);
static void HandleUSR2(int);
static int CheckMask(int, ...);


main()
{
	struct sigaction sigact;

	sigact.sa_handler = HandleUSR1;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	if (sigaction(SIGUSR1, &sigact, 0) == -1) {
		fprintf(stderr, "Unable handle signal USR1\n");
		return 1;
	}
	sigact.sa_handler = HandleUSR2;
	if (sigaction(SIGUSR2, &sigact, 0) == -1) {
		fprintf(stderr, "Unable handle signal USR2\n");
		return 1;
	}

    raise(SIGUSR1);

    if (!CheckMask(0))
        return 1;
    return 0;
}


static void HandleUSR1(int sig)
{
    if (!CheckMask(SIGUSR1, 0))
        exit(1);
    raise(SIGUSR2);
}


static void HandleUSR2(int sig)
{
    if (!CheckMask(SIGUSR1, SIGUSR2, 0))
        exit(1);
}


static int CheckMask(int sig, ...)
{
    sigset_t curMask;
    sigset_t checkMask;
    va_list ap;
    int ret;

    sigprocmask(SIG_SETMASK, 0, &curMask);

    sigemptyset(&checkMask);
    if (sig != 0)
    {
        sigaddset(&checkMask, sig);

        va_start(ap, sig);
        while ((sig = va_arg(ap, int)))
            sigaddset(&checkMask, sig);
        va_end(ap);
    }

    ret = 1;
    for (sig = 1;  sig < 32;  sig++)
    {
        if (!sigismember(&curMask, sig) && sigismember(&checkMask, sig))
        {
            fprintf(stderr, "Mask missing signal %d\n", sig);
            ret = 0;
        }
        if (sigismember(&curMask, sig) && !sigismember(&checkMask, sig))
        {
            fprintf(stderr, "Mask unexpectedly has signal %d\n", sig);
            ret = 0;
        }
    }

    return ret;
}
