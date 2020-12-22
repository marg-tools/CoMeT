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

PUBLIC operImmCmds

.code

; Includes several examples of commands that include immediate operands,
; to be analysed by the tool to extract and display the operand values 
operImmCmds PROC
   BEGIN_STACK_FRAME
   mov RETURN_REG, PARAM1
   add RETURN_REG, 10h
   mov al, 1
   mov cx, 2
   mov edx, 3
ifdef TARGET_IA32
   add ax, -4
else
   add rax, -4
endif
   END_STACK_FRAME
   ret
operImmCmds ENDP

end
