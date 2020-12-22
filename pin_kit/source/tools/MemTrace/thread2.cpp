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


#if defined(TARGET_WINDOWS)
#include <windows.h>
#define EXPORT_CSYM extern "C" __declspec( dllexport )

#else
#define EXPORT_CSYM extern "C" 

#endif

int a[100000];
int n = 10;
long numthreads = 16;
EXPORT_CSYM unsigned int numthreadsStarted = 0;

extern "C" void AtomicIncrement();

EXPORT_CSYM void  DoWork()
{
    int i,j;
    
    for (j = 0; j < 1000; j++)
    {
        for (i = 0; i < n; i++)
        {
            a[i] = 1;
        }
    }
}


EXPORT_CSYM void WaitForAllThreadsStarted()
{
    AtomicIncrement(); // atomically increments numthreadsStarted 
    while (numthreadsStarted != numthreads)
    {
    }
}

EXPORT_CSYM void * ThreadStart(void * arg)
{
    int i;
    // no thread starts the work loop until all threads are in the ThreadStart function
    WaitForAllThreadsStarted();
    for (i = 0; i< 100; i++)
    {
        DoWork();
    }
    return (NULL);
}



THREAD_HANDLE threads[MAXTHREADS];

EXPORT_CSYM int main(int argc, char *argv[])
{
    int i,j;

    for (i = 0; i < numthreads; i++)
    {
        CreateOneThread(&threads[i], ThreadStart, 0);
    }

    for (i = 0; i < numthreads; i++)
    {
        BOOL success;
        success = JoinOneThread (threads[i]);
    }

    return 0;
}
