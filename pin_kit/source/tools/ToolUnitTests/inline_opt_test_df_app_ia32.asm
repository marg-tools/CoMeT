; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.


PUBLIC MyMemCpy




.686
.XMM
.model flat, c



.code

MyMemCpy PROC
    push ebp
	mov  ebp, esp
	push esi
	push edi
	mov  esi, DWORD PTR [ebp+8h]
	mov  edi, DWORD PTR [ebp+0ch]
	mov  ecx, DWORD PTR [ebp+10h]
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
    movsb
	pop edi
	pop esi
	mov eax, 01h
	leave
    ret
MyMemCpy ENDP

end