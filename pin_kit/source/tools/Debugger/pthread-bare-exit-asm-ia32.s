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
#if defined(TARGET_MAC)
    sub     $8, %esp	# On function entry stack is aligned to 12%16 (0x...C)since return IP was pushed to stack, 
    					# moving down to 4%12
    push    $0     # first argument: exit code, stack is aligned to 16 bits
    sub     $4, %esp	# This mimics what call instruction does (push return IP), This is what syscall expect.
    movl    $361,%eax     # system call number (bthread_terminate) - exit thread
#elif defined(TARGET_LINUX)
    movl    $0,%ebx     # first argument: exit code
    movl    $1,%eax     # system call number (sys_exit) - exit thread
#endif


.globl BareExitTrap
BareExitTrap:
    int     $0x80       # call kernel
