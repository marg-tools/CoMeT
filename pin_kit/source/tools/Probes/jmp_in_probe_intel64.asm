; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC probed_func_asm


.code
probed_func_asm PROC
    xor rax, rax
    cmp rcx, 0
    jne $lNOT_ZERO
    mov rax, 2
$lNOT_ZERO:
    mov rax, 1
    ret

probed_func_asm ENDP

end