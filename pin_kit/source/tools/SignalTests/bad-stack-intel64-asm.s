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
#if defined(TARGET_MAC)
.globl _DoILLOnBadStack
_DoILLOnBadStack:
#else
.globl DoILLOnBadStack
DoILLOnBadStack:
#endif
    movq    %rsp, %rax
    movq    $0, %rsp
    ud2
    movq    %rax, %rsp
    ret

#if defined(TARGET_MAC)
.globl _DoSigreturnOnBadStack
_DoSigreturnOnBadStack:
#else
.globl DoSigreturnOnBadStack
DoSigreturnOnBadStack:
#endif
    push    %rbp
    movq    %rsp, %rbp
    movq    $0, %rsp
#if defined(TARGET_LINUX)
    movq    $15, %rax    /* __NR_rt_sigreturn */
#elif defined(TARGET_BSD)
    movq    $417, %rax    /* SYS_sigreturn */
#elif defined(TARGET_MAC)
    movq    $0, %rdi
    movq    $30, %rsi
    movq    $0x020000b8, %rax  /* SYS_sigreturn */
#else
#error "Code not defined"
#endif
    syscall
    movq    %rbp, %rsp
    pop     %rbp
    ret
