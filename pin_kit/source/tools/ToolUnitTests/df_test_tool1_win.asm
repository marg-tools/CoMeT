; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC TestDfByReadFlags


.686
.model flat, c
extern numTimesDfIsSet:word
.code
TestDfByReadFlags PROC
    pushfd       
    pop        eax
    and        eax, 1024
    shr        eax, 10
    lea        ecx, numTimesDfIsSet
    add        DWORD PTR [ecx], eax
    ret

TestDfByReadFlags ENDP

end