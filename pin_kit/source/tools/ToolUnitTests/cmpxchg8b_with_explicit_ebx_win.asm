; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC cmpxchg8_with_explicit_ebx


.686
.model flat, c
extern eaxVal:dword
extern edxVal:dword
extern a:dword
.code
cmpxchg8_with_explicit_ebx PROC

    lea ecx,a
    mov ebx, ecx
    mov eax, 0
    mov edx, 0
    cmpxchg8b QWORD PTR [ebx+eax]
    lea ecx,eaxVal
    mov DWORD PTR [ecx], eax
    lea ecx,edxVal
    mov DWORD PTR [ecx], edx
    
    ret

cmpxchg8_with_explicit_ebx ENDP


	
end
