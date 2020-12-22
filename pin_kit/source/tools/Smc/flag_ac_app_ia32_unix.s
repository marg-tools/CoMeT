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



.global SetAppFlags_asm
.type SetAppFlags_asm, @function


SetAppFlags_asm:

    push %ebp
	mov  %esp, %ebp
	mov  8(%ebp), %eax
    pushf
    pop %ecx
    or %eax, %ecx
    mov %eax, %edx
    push %ecx
    popf
    leave
    ret


.global ClearAcFlag_asm
.type ClearAcFlag_asm, @function
ClearAcFlag_asm: 

    
    pushf
    pop %ecx
    and $0xfffbffff, %ecx
    push %ecx
    popf
    ret

    .align 4
.globl GetFlags_asm
.type GetFlags_asm, @function
GetFlags_asm:
    pushf
    pop %eax
    ret
