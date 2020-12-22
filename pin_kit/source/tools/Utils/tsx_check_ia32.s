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
.global _SupportsTsx
_SupportsTsx:
#else
.global SupportsTsx
SupportsTsx:
#endif
    push %ebp
    mov  %esp, %ebp
    

    .balign 1 ; .byte 0xc7
    .balign 1 ; .byte 0x58
    .balign 1 ; .byte 0x02
    .balign 1 ; .byte 0x00
    .balign 1 ; .byte 0x00
    .balign 1 ; .byte 0x00
    jmp successLabel
abortLabel:
    mov $0, %eax
    jmp returnLabel
successLabel:
    mov $1, %eax
    .balign 1 ; .byte 0x0f
    .balign 1 ; .byte 0x01
    .balign 1 ; .byte 0xd5
returnLabel:
    mov %ebp, %esp
    pop %ebp
    ret
