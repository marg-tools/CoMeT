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

#include <assert.h>
#include <stdio.h>
#include "../Utils/threadlib.h"

int a[100000];
int n = 10;

void * hello(void * arg)
{
    int i,j;
    
    //printf("In child %d: %p \n", getpid(), arg);
    //fflush(stdout);
    //kill(0,SIGSTOP);
    
    for (j = 0; j < 1000; j++)
    {
        for (i = 0; i < n; i++)
        {
            a[i] = 1;
        }
    }

    return 0;
}

THREAD_HANDLE threads[MAXTHREADS];

int threads_started;

int main(int argc, char *argv[])
{
    int numthreads = 5;
    int numreps = 1000;
    int success;
    
    int i,j;
    
    //sscanf(argv[1], "%d", &numthreads);
    printf("Threads: %d * reps: %d\n", numthreads, numreps);
    
    assert(numthreads < MAXTHREADS);
    
    for (j = 0; j < numreps; j++)
    {
        
        for (i = 0; i < numthreads; i++)
        {
            //printf("Creating thread\n");
            //fflush(stdout);
            if (!CreateOneThread(&threads[i], hello, 0))
            {
                fprintf(stdout, "CreateOneThread failed\n");
            }
            fflush(stdout);
        }
        for (i = 0; i < numthreads; i++)
        {
            BOOL success;
            success = JoinOneThread(threads[i]);
            if (!success)
            {
                fprintf(stdout, "JoinOneThread failed\n");
                fflush (stdout);
            }
        }

        printf("Finished rep %d\n", j);
        fflush (stdout);
    }
    
    printf("All threads joined\n");
    fflush (stdout);

    return 0;
}
