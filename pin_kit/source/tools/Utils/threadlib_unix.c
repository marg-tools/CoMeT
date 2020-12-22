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


/*! @file
 *  Implementation of the threading API in Unix. 
 */

#include "threadlib.h"
#include <sched.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#if defined(TARGET_LINUX)
#include <sys/syscall.h>
/*
 * Get thread Id
 */
unsigned long GetTid()
{
     return (unsigned long)syscall(__NR_gettid);
}
#elif defined(TARGET_MAC)
#include <mach/mach.h>
/*
 * Get thread Id
 */
unsigned long GetTid()
{
     return mach_thread_self();
}
#endif

BOOL CreateOneThread(THREAD_HANDLE * pThreadHandle, THREAD_RTN_PTR threadRtn, void * arg)
{
    pthread_t pthreadId;
    int rval;

    rval = pthread_create(&pthreadId, 0, threadRtn, arg);
    if (rval != 0) {
        perror("thread");
        fprintf(stdout, "pthread_create() failed with code: %d\n", rval);
        fflush(stdout);
        return FALSE;
    }

    *pThreadHandle = (THREAD_HANDLE)pthreadId;
    return TRUE;
}

BOOL JoinOneThread(THREAD_HANDLE threadHandle)
{
    pthread_t pthreadId = (pthread_t)threadHandle;
    int status = pthread_join(pthreadId, 0);
    return (status==0) ? TRUE : FALSE;
}

void ExitCurrentThread()
{
    pthread_exit(0);
}

void DelayCurrentThread(unsigned int millisec)
{
#if defined(TARGET_LINUX)
    sched_yield();
#endif
    usleep(millisec*1000);
}
