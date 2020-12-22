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

/*
 * void CopyWithMovsb(void *src, void *dst, size_t size)
 */
.text
    .align 4
#if defined(TARGET_MAC)
.globl _CopyWithMovsb
_CopyWithMovsb:
#else
.globl CopyWithMovsb
CopyWithMovsb:
#endif
    xchg    %rdi, %rsi  /* src, dst */
    mov     %rdx, %rcx  /* size */
    rep movsb
    ret
