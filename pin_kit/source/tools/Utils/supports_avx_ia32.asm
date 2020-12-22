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
 ProcessorSupportsAvx PROC
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
    jmp $lDONE3
$lNOT_SUPPORTED:
    popa
    mov eax, 0
$lDONE3:
    mov     esp, ebp
    pop     ebp
    ret
ProcessorSupportsAvx ENDP

END