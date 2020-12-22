; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.


PUBLIC maina
PUBLIC red
PUBLIC blue
PUBLIC common
.686
.model flat, c
.code
maina PROC	
	mov eax,0
	cmp eax,0
    call red
	call blue
	mov eax,1
	cmp eax,0
	call red
	call blue
	ret
maina ENDP
	

red PROC		
	jz r2
	jmp common
r2:
	jmp common
red ENDP
	

blue PROC		
	jz b2
	jmp common
b2:	
	jmp common
blue ENDP
	

common PROC
	ret
common ENDP
						
end