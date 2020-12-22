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

PUBLIC bsr_func
PUBLIC bsf_func

.code

; int bsr_func(int src) - this function returns the bit index of the 
; most significant bit set. in case 'src' is zero, -1 is returned.
bsr_func PROC
   BEGIN_STACK_FRAME
   mov RETURN_REG, 0
   not RETURN_REG
   bsr RETURN_REG, PARAM1
   END_STACK_FRAME
   ret
bsr_func ENDP

; int bsf_func(int src) - this function returns the bit index of the 
; least significant bit set. in case 'src' is zero, -1 is returned.
bsf_func PROC
   BEGIN_STACK_FRAME
   mov RETURN_REG, 0
   not RETURN_REG
   bsf RETURN_REG, PARAM1
   END_STACK_FRAME
   ret
bsf_func ENDP

end
