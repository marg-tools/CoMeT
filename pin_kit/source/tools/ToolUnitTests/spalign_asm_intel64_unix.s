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
 * If the stack is properly aligned, "SP-8" should be aligned on a 16-byte boundary
 * on entry to this (and any) function.  The 'movdqa' instruction below will fault
 * if the stack is not aligned this way.
 */

.text
    .align 4
#ifdef TARGET_MAC
.globl _CheckSPAlign
_CheckSPAlign:
#else
.globl CheckSPAlign
CheckSPAlign:
#endif
    add     $-24, %rsp
    movdqa  %xmm0, 0(%rsp)
    add     $24, %rsp
    ret
