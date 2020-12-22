; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC SetAppFlags_asm
PUBLIC ClearAcFlag_asm
PUBLIC GetFlags_asm


.686
.model flat, c


.code
SetAppFlags_asm PROC

    push ebp
	mov  ebp, esp
	mov  eax, DWORD PTR [ebp+8h]
    pushfd
    pop ecx
    or ecx, eax
    mov edx, eax
    push ecx
    popfd
    leave
    ret

SetAppFlags_asm ENDP

ClearAcFlag_asm PROC

    
    pushfd
    pop ecx
    and ecx, 0fffbffffH
    push ecx
    popfd
    ret

ClearAcFlag_asm ENDP


GetFlags_asm PROC

    
    pushfd
    pop eax
    ret

GetFlags_asm ENDP

end