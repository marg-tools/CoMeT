; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC ZeroOutScratches
PUBLIC SetIntegerScratchesTo1





.686
.XMM
.model flat, c



.code
ZeroOutScratches PROC
    
    xor eax, eax
    xor ecx, ecx
    xor edx, edx
    pxor xmm0, xmm0
    pxor xmm1, xmm1
    pxor xmm2, xmm2
    pxor xmm3, xmm3
    pxor xmm4, xmm4
    pxor xmm5, xmm5
    pxor xmm6, xmm6
    pxor xmm7, xmm7
    ret

ZeroOutScratches ENDP


SetIntegerScratchesTo1 PROC
    xor eax, eax
    inc eax
    xor edx, edx
    inc edx
    xor ecx, ecx
    inc ecx
    ret

SetIntegerScratchesTo1 ENDP




end