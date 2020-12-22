/*
 * Copyright 2002-2019 Intel Corporation.
 * 
 * This software and the related documents are Intel copyrighted materials, and your
 * use of them is governed by the express license under which they were provided to
 * you ("License"). Unless the License provides otherwise, you may not use, modify,
 * copy, publish, distribute, disclose or transmit this software or the related
 * documents without Intel's prior written permission.
 * 
 * This software and the related documents are provided as is, with no express or
 * implied warranties, other than those that are expressly stated in the License.
 */

// <COMPONENT>: os-apis
// <FILE-TYPE>: component public header

#ifndef OS_APIS_SIGACTION_KERNEL_H
#define OS_APIS_SIGACTION_KERNEL_H

#include "os-apis.h"

// The kernel's sigaction struct is different than the struct
// defined in signal.h.
// We need to define it here in order to pass it correctly to the kernel
#if defined(TARGET_LINUX)
typedef struct /*<POD>*/ kernel_sigaction 
{
    void(*_handler)(int);
    unsigned long _flags;
    void(*_restorer)(void);
    UINT64 _mask;
} SIGACTION_KERNEL;
#else // not TARGET_LINUX
typedef struct /*<POD>*/ kernel_sigaction
{
    void(*_handler)(int);
    void(*_tramp)(void *, unsigned int, int, void *, void *);
    UINT32 _mask;
    UINT32 _flags;
} SIGACTION_KERNEL;
#endif  // not TARGET_LINUX

#endif // file guard
