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
.align 4

#ifdef TARGET_MAC
.globl _ProcessorSupportsAvx;
_ProcessorSupportsAvx:
#else
.globl ProcessorSupportsAvx;
ProcessorSupportsAvx:
#endif
    push %rbp
    mov  %rsp, %rbp
    push %rax
    push %rbx
    push %rcx
    push %rdx
    push %rsi

    mov $1, %rax

    cpuid

    and $0x018000000, %ecx
    cmp $0x018000000, %ecx
    jne .lNOT_SUPPORTED
    mov $0, %ecx

    # command name
    .byte 0x0F, 0x01, 0xD0

    and $6, %eax
    cmp $6, %eax
    jne .lNOT_SUPPORTED
    mov $1, %rax
    jmp .lDONE3
.lNOT_SUPPORTED:
    mov $0, %rax

.lDONE3:
    pop %rsi
    pop %rdx
    pop %rcx
    pop %rbx

    mov %rbp, %rsp
    pop %rbp
    ret

