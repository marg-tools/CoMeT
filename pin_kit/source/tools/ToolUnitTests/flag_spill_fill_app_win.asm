; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC SetAppFlags_asm


.686
.model flat, c
extern flagsVal:dword

.code
SetAppFlags_asm PROC
    pushfd
    pop eax
    mov edx, eax
    or eax, 0cd5H
    push eax
    popfd
    pushfd
    pop eax
    lea ecx,flagsVal
    mov       DWORD PTR [ecx], eax
    push edx
    popfd
    ret

SetAppFlags_asm ENDP

end