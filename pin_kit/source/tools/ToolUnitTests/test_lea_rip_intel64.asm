; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.




.code

VerifyLeaRip PROC
    
	push rbx
    ;cannot write rbx, [rip]  in masm
    DB 48h, 8Dh, 1Dh, 00h, 00h, 00h, 00h
	call VerifyLeaLab1
VerifyLeaLab1:
    pop rdx
	xor rax,rax
	add rbx, 5
	cmp rdx, rbx
	je VerifyLeaLabNextTest
	pop rbx
    ret
VerifyLeaLabNextTest:
     ;cannot write rbx, [rip+5]  in masm
    DB 48h, 8Dh, 1Dh, 05h, 00h, 00h, 00h
	call VerifyLeaLab2
VerifyLeaLab2:
    pop rdx
	cmp rdx, rbx
	je VerifyLeaLabPassed
	pop rbx
    ret
VerifyLeaLabPassed:
    inc rax
    pop rbx
    ret
VerifyLeaRip ENDP


end