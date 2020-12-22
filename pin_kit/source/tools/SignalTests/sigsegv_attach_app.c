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

#include <sys/types.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

extern void DoRelease(volatile bool* doRelease)
{
    // do nothing
}


static void WaitForAttach()
{
    const unsigned int timeout = 300;
    unsigned int releaseCounter = 0;
    volatile bool released = false;
    while (!released)
    {
        if (releaseCounter >= timeout )
        {
            printf("APP ERROR: Timeout reached and the tool did not release the application.\n");
            exit(1);
        }
        ++releaseCounter;
        DoRelease(&released);
        sleep(1);
    }
}


void sig_handler_1(int unused) {
    printf("Caught signal SIGSEGV \n");
}

int main() {
    signal(SIGSEGV, sig_handler_1);
    printf("Test process: %d\n", getpid());

    WaitForAttach();
    pthread_kill(pthread_self(), SIGSEGV);

    return 0;
}

