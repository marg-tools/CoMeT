; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC SupportsAvx
PUBLIC Do_Xsave
PUBLIC Do_Fxsave
PUBLIC Do_Xrstor
PUBLIC Do_Fxrstor


.code
SupportsAvx PROC
    push    rbp
    mov     rbp, rsp
    push    rax
    push    rbx
    push    rcx
    push    rdx
    push    rsi

    mov     rax, 1      

    cpuid

    and ecx, 0018000000h
    cmp ecx, 0018000000h 
    jne $lNOT_SUPPORTED 
    mov ecx, 0          
    
    BYTE 00Fh
    BYTE 001h
    BYTE 0D0h
    and eax, 6
    cmp eax, 6        
    jne $lNOT_SUPPORTED
    mov rax, 1
    jmp $lDONE3
$lNOT_SUPPORTED:
    mov rax, 0
$lDONE3:
    pop    rsi
    pop    rdx
    pop    rcx
    pop    rbx

    mov     rsp, rbp
    pop     rbp
    ret
SupportsAvx ENDP

.code
Do_Xsave PROC
    xor rdx,rdx
    mov rax,7
 
    ret
Do_Xsave ENDP

.code
Do_Fxsave PROC
    fxsave xmmword ptr[rcx]
    ret
Do_Fxsave ENDP

.code
Do_Xrstor PROC
    xor rdx,rdx
    mov rax,7
    
    ret
Do_Xrstor ENDP

.code
Do_Fxrstor PROC
    fxrstor xmmword ptr[rcx]
    ret
Do_Fxrstor ENDP

end
