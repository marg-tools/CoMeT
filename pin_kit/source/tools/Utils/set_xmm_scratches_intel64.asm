; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.




PUBLIC SetXmmScratchesFun
extern xmmInitVals:dword

.code
SetXmmScratchesFun PROC
    lea rax,xmmInitVals
    movdqu xmm0, xmmword ptr [rax]
    movdqu xmm1, xmmword ptr [rax]+32
    movdqu xmm2, xmmword ptr [rax]+64
    movdqu xmm3, xmmword ptr [rax]+96
    movdqu xmm4, xmmword ptr [rax]+128
    movdqu xmm5, xmmword ptr [rax]+160
    
    ret
SetXmmScratchesFun ENDP

end