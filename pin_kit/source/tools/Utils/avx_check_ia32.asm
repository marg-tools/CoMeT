; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC SupportsAvx


.686
.model flat, c

.code
 ALIGN 4 
 SupportsAvx PROC
    push    ebp
    mov     ebp, esp
    pusha

    mov     eax, 1

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
    popa
    mov eax, 1
    jmp $lDONE
$lNOT_SUPPORTED:
    popa
    mov eax, 0
$lDONE:
    mov     esp, ebp
    pop     ebp
    ret
SupportsAvx ENDP

end
