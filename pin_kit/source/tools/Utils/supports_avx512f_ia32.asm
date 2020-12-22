; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC SupportsAvx512f


.686
.model flat, c

.code
 ALIGN 4
 SupportsAvx512f PROC
    push ebp
    mov ebp, esp
    pusha
    mov eax, 1
    cpuid
    and ecx, 0018000000h
    cmp ecx, 0018000000h
    jne $lNOT_SUPPORTED
    mov ecx, 0

    BYTE 00Fh
    BYTE 001h
    BYTE 0D0h
    and eax, 066h
    cmp eax, 066h
    jne $lNOT_SUPPORTED
    mov eax, 7
    mov ecx, 0
    cpuid
    and ebx, 010000h
    cmp ebx, 010000h
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
SupportsAvx512f ENDP

end
