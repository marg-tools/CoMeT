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
 * This test verifies that Pin correctly clears the DF bit when executing
 * the application's signal handler.
 *
 * This test may also be run natively, bit it fails on older kernels
 * because older kernels did not correctly clear DF on entry to a signal
 * handler.  (The same bug Pin used to have.)
 */

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>


int DidTest;
int DFSet = 0;
int Flags;

extern void SetAndClearDF();
extern void SignalHandler(int);


int main()
{
    struct sigaction sigact;
    struct itimerval itval;


    sigact.sa_handler = SignalHandler;
    sigact.sa_flags = 0;
    sigemptyset(&sigact.sa_mask);
    if (sigaction(SIGALRM, &sigact, 0) == -1)
    {
        fprintf(stderr, "Unable to set up handler\n");
        return 1;
    }

    itval.it_interval.tv_sec = 0;
    itval.it_interval.tv_usec = 100000;
    itval.it_value.tv_sec = 0;
    itval.it_value.tv_usec = 100000;
    if (setitimer(ITIMER_REAL, &itval, 0) == -1)
    {
        fprintf(stderr, "Unable to set up timer\n");
        return 1;
    }

    /*
     * Continuously set and clear the DF bit until a signal arrives while DF is set.
     */
    while (!DidTest)
        SetAndClearDF();

    itval.it_value.tv_sec = 0;
    itval.it_value.tv_usec = 0;
    if (setitimer(ITIMER_REAL, &itval, 0) == -1)
    {
        fprintf(stderr, "Unable to disable timer\n");
        return 1;
    }

    /*
     * The signal handler copied the flags to 'Flags'.  Make sure the DF bit was
     * cleared in the handler.
     */
    if (Flags & (1<<10))
    {
        fprintf(stderr, "DF bit set incorrectly in signal handler\n");
        return 1;
    }
    return 0;
}
