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
    movdqu   (%rdi), %xmm0
    movdqu   16(%rdi), %xmm1
    movdqu   32(%rdi), %xmm2
    movdqu   48(%rdi), %xmm3
    movdqu   64(%rdi), %xmm4
    movdqu   80(%rdi), %xmm5
    movdqu   96(%rdi), %xmm6
    movdqu   112(%rdi), %xmm7
    movdqu   128(%rdi), %xmm8
    movdqu   144(%rdi), %xmm9
    movdqu   160(%rdi), %xmm10
    movdqu   176(%rdi), %xmm11
    movdqu   192(%rdi), %xmm12
    movdqu   208(%rdi), %xmm13
    movdqu   224(%rdi), %xmm14
    movdqu   240(%rdi), %xmm15
    
    ret

