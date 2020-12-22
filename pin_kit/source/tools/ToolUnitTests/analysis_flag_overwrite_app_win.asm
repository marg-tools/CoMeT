; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC main_asm


.686
.model flat, c
extern addcVal:word

.code
main_asm PROC
    mov eax,-1
    mov edx,0
    add eax,1
    adc edx,0
    lea ecx,addcVal
    mov       DWORD PTR [ecx], edx
    ret

main_asm ENDP

end