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
#include <string.h>
#include <pthread.h>

static void Handle(int);


int main(int argc, char **argv)
{
    int setHandler;
    struct sigaction act;


    if (argc == 2 && strcmp(argv[1], "yes") == 0)
    {
        setHandler = 1;
    }
    else if (argc == 2 && strcmp(argv[1], "no") == 0)
    {
        setHandler = 0;
    }
    else
    {
        fprintf(stderr, "Specify either 'yes' or 'no'\n");
        return 1;
    }

    if (setHandler)
    {
        act.sa_handler = Handle;
        act.sa_flags = 0;
        sigemptyset(&act.sa_mask);
        if (sigaction(SIGUSR1, &act, 0) != 0)
        {
            fprintf(stderr, "Unable to set up USR1 handler\n");
            return 1;
        }
    }

    pthread_kill(pthread_self(), SIGUSR1);
    printf("Application did not get SIGUSR1\n");

    return 0;
}


static void Handle(int sig)
{
    printf("Application got SIGUSR1\n");
    exit(0);
}
