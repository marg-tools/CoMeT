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
.global probed_func_asm
.type probed_func_asm,  @function
probed_func_asm:
    xor %rax, %rax
    cmp $0, %rcx
    jne NOT_ZERO
    mov $2, %rax
NOT_ZERO:
    mov $1, %rax
    ret
