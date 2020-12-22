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
#if defined(TARGET_MAC)
.globl _SetAppFlagsAndSegv_asm
_SetAppFlagsAndSegv_asm:
#else
.globl SetAppFlagsAndSegv_asm
SetAppFlagsAndSegv_asm:
#endif
    pushf
    pop %eax
    or $0xcd5, %eax
    push %eax
    popf
    mov  $7, %ecx
    mov  %eax, 0(%ecx)
    ret

    .align 4
#if defined(TARGET_MAC)
.globl _ClearAppFlagsAndSegv_asm
_ClearAppFlagsAndSegv_asm:
#else
.globl ClearAppFlagsAndSegv_asm
ClearAppFlagsAndSegv_asm:
#endif
    pushf
    pop %eax
    and $0xfffff000, %eax
    push %eax
    popf
    mov  $7, %ecx
    mov  %eax, 0(%ecx)
    ret
    
    .align 4
#if defined(TARGET_MAC)
.globl _GetFlags_asm
_GetFlags_asm:
#else
.globl GetFlags_asm
GetFlags_asm:
#endif
    pushf
    pop %eax
    ret
