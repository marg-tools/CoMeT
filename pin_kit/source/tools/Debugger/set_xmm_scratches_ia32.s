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
.globl SetXmmScratchesFun
SetXmmScratchesFun:
    push      %ebp
    mov       %esp, %ebp
    mov       8(%ebp), %eax
    movdqu   (%eax),%xmm0
    movdqu   16(%eax),%xmm1
    movdqu   32(%eax),%xmm2
    movdqu   48(%eax),%xmm3
    movdqu   64(%eax),%xmm4
    movdqu   80(%eax),%xmm5
    movdqu   96(%eax),%xmm6
    movdqu   112(%eax),%xmm7
    pop       %ebp
    ret


