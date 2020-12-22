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
    push %ebp
    mov  %esp, %ebp
    pusha

    mov $1, %eax

    cpuid

    and  $0x018000000, %ecx
    cmp  $0x018000000, %ecx
    jne .lNOT_SUPPORTED
    mov $0, %ecx

    .balign 1 ; .byte 0x0F
    .balign 1 ; .byte 0x01
    .balign 1 ; .byte 0xD0
    and $6, %eax
    cmp $6, %eax
    jne .lNOT_SUPPORTED
    popa
    mov $1, %eax
    jmp .lDONE3
.lNOT_SUPPORTED:
    popa
    mov $0, %eax
.lDONE3:
    mov %ebp, %esp
    pop %ebp
    ret
