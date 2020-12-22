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

    .text
.globl BareExit
BareExit:
    movq    $0,%rdi     # first argument: exit code
#if defined(TARGET_MAC)
    movq    $0x2000169,%rax    # system call number (bthread_terminate) - exit thread
#elif defined(TARGET_LINUX)
    movq    $60,%rax    # system call number (sys_exit) - exit thread
#endif


.globl BareExitTrap
BareExitTrap:
    syscall             # call kernel
