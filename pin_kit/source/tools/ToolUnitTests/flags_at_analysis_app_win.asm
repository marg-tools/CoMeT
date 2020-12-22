; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC SetOfFlag_asm


.686
.model flat, c


.code
SetOfFlag_asm PROC
    xor eax, eax
    inc eax
    pushfd
    popfd
    cmp al, 081H
    xor ecx, ecx
    ret

SetOfFlag_asm ENDP

end