; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC UpdateIcountByAdd
PUBLIC UpdateIcountByInc
PUBLIC UpdateIcountByDecInc
PUBLIC UpdateIcountBySub
PUBLIC IfFuncWithAddThatCannotBeChangedToLea

.code


UpdateIcountByAdd PROC
    
    mov rax, qword ptr [rcx]
	add rax, 1
	mov qword ptr [rcx], rax
    ret
UpdateIcountByAdd ENDP

UpdateIcountByInc PROC
    
    mov rax, qword ptr [rcx]
	inc rax
	mov qword ptr [rcx], rax
    ret
UpdateIcountByInc ENDP

UpdateIcountByDecInc PROC
    
    mov rax, qword ptr [rcx]
	dec rax
	inc rax
	inc rax
	mov qword ptr [rcx], rax
    ret
UpdateIcountByDecInc ENDP

UpdateIcountBySub PROC
    
    mov rax, qword ptr [rcx]
	sub rax, -1
	mov qword ptr [rcx], rax
    ret
UpdateIcountBySub ENDP

IfFuncWithAddThatCannotBeChangedToLea PROC
    xor eax, eax  
    add eax, 1 
    setz al 
    ret
IfFuncWithAddThatCannotBeChangedToLea ENDP

end
