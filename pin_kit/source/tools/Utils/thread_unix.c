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

#include <sched.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAXTHREADS 1000

int data[MAXTHREADS];

void * start(void * arg)
{
    int i = 0;
    for(i = 0; i < 1000; i++)
    {
        void * h =  malloc(13);
        if (h)
            free(h);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    pthread_t threads[MAXTHREADS];
    int i;
    int numthreads = 20;

    printf("Creating %d threads\n", numthreads);

    for (i = 0; i< numthreads; i++)
    {
        pthread_create(&threads[i], 0, start, 0);
    }
    
    for (i = 0; i < numthreads; i++)
    {
        pthread_join(threads[i], 0);
    }
    printf("All threads joined\n");

    return 0;
}

