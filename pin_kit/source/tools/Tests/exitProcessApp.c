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
#include <unistd.h>

// cause an infinite loop at the exit of the app

void sendSignal()
{
    printf("sendSignal SIGUSR1\n");
    kill(getpid(), SIGUSR1);
}

void callSendSignal(int sig)
{
    printf("callSendSignal\n");
    sendSignal();
}

int main()
{
    if (signal(SIGUSR1, callSendSignal) == SIG_ERR)
        exit(1);

    atexit(sendSignal);
    return 0;
}

