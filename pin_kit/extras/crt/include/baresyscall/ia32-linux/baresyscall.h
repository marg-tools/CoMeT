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

#ifndef OS_APIS_LINUX_IA32_BARESYSCALL_H__
#define OS_APIS_LINUX_IA32_BARESYSCALL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

/*!
 * Set of raw return values from a system call.
 */
typedef struct /*<POD>*/
{
    ADDRINT _eax;
    BOOL_T _success;
} OS_SYSCALLRETURN;

/*
 * This is the signal restorer which is called after a signal handler
 * had returned.
 * This is basically a system call to restore the original application's
 * stack.
 * This syscall never returns
 */
void OS_SigReturn();

#ifdef __cplusplus
}
#endif

#endif // file guard
