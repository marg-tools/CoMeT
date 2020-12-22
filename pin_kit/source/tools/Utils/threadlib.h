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
 *  Generic threading API. 
 */

#ifndef THREADLIB_H
#define THREADLIB_H

#ifdef __cplusplus
extern "C" {
#endif

typedef int BOOL;
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define MAXTHREADS 1000

typedef void * THREAD_HANDLE;
typedef void * THREAD_RTN(void * arg);
typedef THREAD_RTN * THREAD_RTN_PTR;

BOOL CreateOneThread(THREAD_HANDLE * pThreadHandle, THREAD_RTN_PTR threadRtn, void * arg);

BOOL JoinOneThread(THREAD_HANDLE threadHandle);

void ExitCurrentThread();

void DelayCurrentThread(unsigned int millisec);

unsigned long GetTid();

#ifdef __cplusplus
}
#endif

#endif  // #ifndef THREADLIB_H
