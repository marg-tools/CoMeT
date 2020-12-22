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

/*
 * These defines are replacers for enum, Since this file is included in an assembly file
 * docall-ia32-mac-asm.spp we cannot use anything but defines
 */
#define OS_SYSCALL_TYPE_LINUX      0
#define OS_SYSCALL_TYPE_WIN        1
#define OS_SYSCALL_TYPE_SYSENTER   2
#define OS_SYSCALL_TYPE_WOW64      3
#define OS_SYSCALL_TYPE_INT80      4
#define OS_SYSCALL_TYPE_INT81      5
#define OS_SYSCALL_TYPE_INT82      6
#define OS_SYSCALL_TYPE_INT83      7
#define OS_SYSCALL_TYPE_UNIX   OS_SYSCALL_TYPE_SYSENTER
