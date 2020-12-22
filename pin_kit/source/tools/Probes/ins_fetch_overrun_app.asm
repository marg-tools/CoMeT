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

.code
PUBLIC foo                        
foo PROC
        BEGIN_STACK_FRAME
        END_STACK_FRAME
        call GAX_REG
foo ENDP
        BYTE 0h
PUBLIC bar
bar PROC
        BEGIN_STACK_FRAME
        mov  RETURN_REG, 1ee7h
        END_STACK_FRAME
        ret
bar ENDP

END
