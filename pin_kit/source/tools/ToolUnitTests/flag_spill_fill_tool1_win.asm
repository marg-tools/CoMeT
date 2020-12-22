; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC ZeroAppFlags_asm

.686
.model flat, c
.code
ZeroAppFlags_asm PROC
    pushfd
    pop eax
    and eax, 0fffff326H
    push eax
    popfd
    ret

ZeroAppFlags_asm ENDP

end