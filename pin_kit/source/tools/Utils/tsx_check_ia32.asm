; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

.686
.xmm
.model flat,c

ASSUME NOTHING

.CODE 
 ALIGN 4 
 SupportsTsx PROC
    push    ebp
    mov     ebp, esp
    BYTE 0C7h
    BYTE 0F8h
    BYTE 002h
    BYTE 000h
    BYTE 000h
    BYTE 000h

    jmp successLabel
abortLabel:
    mov eax, 0
    jmp returnLabel
successLabel:
    mov eax, 1

    BYTE 00fh
    BYTE 001h
    BYTE 0d5h

returnLabel:
    mov     esp, ebp
    pop     ebp
    ret
SupportsTsx ENDP

END