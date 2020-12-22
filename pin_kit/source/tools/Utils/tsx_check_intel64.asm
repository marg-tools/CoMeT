; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.


.CODE 
 ALIGN 4 
 SupportsTsx PROC
    push    rbp
    mov     rbp, rsp
    push    rax
    push    rbx
    push    rcx
    push    rdx
    push    rsi       
    
    BYTE 0C7h
    BYTE 0F8h
    BYTE 002h
    BYTE 000h
    BYTE 000h
    BYTE 000h

    jmp successLabel
abortLabel:
    mov rax, 0
    jmp returnLabel
successLabel:
    mov rax, 1

    BYTE 00fh
    BYTE 001h
    BYTE 0d5h

returnLabel:
    pop    rsi
    pop    rdx
    pop    rcx
    pop    rbx

    mov     rsp, rbp
    pop     rbp
    ret
SupportsTsx ENDP

END