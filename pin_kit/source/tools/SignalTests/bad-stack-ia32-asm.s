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

    movl    %esp, %eax
    movl    $0, %esp
    ud2
    movl    %eax, %esp
    ret

#if defined(TARGET_MAC)
.globl _DoSigreturnOnBadStack
_DoSigreturnOnBadStack:
#else
.globl DoSigreturnOnBadStack
DoSigreturnOnBadStack:
#endif
    push    %ebp
    movl    %esp, %ebp
#if defined(TARGET_LINUX)
    movl    $0, %esp
    movl    $119, %eax      /* __NR_sigreturn */
    int     $128
#elif defined(TARGET_MAC)
    movl    $0, %esp
    movl    $0xb8, %eax     /* SYS_sigreturn */
    int     $0x80
#else
#error "Code not defined"
#endif
    movl    %ebp, %esp
    pop     %ebp
    ret
