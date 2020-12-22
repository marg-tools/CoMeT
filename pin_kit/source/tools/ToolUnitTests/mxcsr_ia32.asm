; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC GetMxcsr
PUBLIC SetMxcsr


.686
.XMM
.model flat, c

.code
GetMxcsr PROC
    push ebp
	mov  ebp, esp
	mov  eax, DWORD PTR [ebp+8h]
	stmxcsr DWORD PTR [eax]
	leave
    ret

GetMxcsr ENDP

SetMxcsr PROC
    push ebp
	mov  ebp, esp
	mov  eax, DWORD PTR [ebp+8h]
	ldmxcsr DWORD PTR [eax]
	leave
    ret

SetMxcsr ENDP

end