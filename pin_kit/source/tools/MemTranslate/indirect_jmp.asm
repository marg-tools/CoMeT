; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

include asm_macros.inc

PROLOGUE

PUBLIC main

.code

main PROC
    lea RETURN_REG,next_line
    push RETURN_REG
    mov RETURN_REG,0fedh 
; This is a jmp with bad address, but it will be translated to "jmp *(rsp)"
    jmp ADDRINT_PTR [RETURN_REG]
next_line:
    pop RETURN_REG
    mov RETURN_REG,0
    ret
main ENDP

end
