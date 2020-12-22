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

#ifndef OS_APIS_BARESYSCALL_H__
#define OS_APIS_BARESYSCALL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "syscalltypes.h"

typedef int OS_SYSCALL_TYPE;

#if defined(TARGET_WINDOWS)

#include "windows-baresyscall.h"

#endif

#if defined(TARGET_LINUX)

#include "linux-baresyscall.h"

#endif

#if defined(TARGET_MAC)

#include "mac-baresyscall.h"

#endif

/*!
 * Perform a system call.
 * @param[in] sysno        The system call number.
 * @param[in] type         The system call type (linux, int80 , int81 ....).
 * @param[in] argCount     The number of system call parameters.
 * @param[in] ...          A variable number of system call parameters.
 *
 * @return  Returns a OS_SYSCALLRETURN object, which can be used to
 *          examine success and result values.
 */
OS_SYSCALLRETURN OS_SyscallDo(ADDRINT sysno, OS_SYSCALL_TYPE type, unsigned argCount, ...);


#ifdef __cplusplus
}
#endif

#endif // file guard
