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

#include <asm_macros.h>

DECLARE_FUNCTION(main)

.global NAME(main)

NAME(main):
    lea PIC_VAR(next_line),RETURN_REG
    push RETURN_REG
    mov $0xfed,RETURN_REG
// This is a jmp with bad address, but it will be translated to "jmp *(rsp)"
    jmp *(RETURN_REG)
next_line:
    pop RETURN_REG
    mov $0,RETURN_REG
    ret

