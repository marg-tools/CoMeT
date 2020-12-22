; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

.386
.XMM
.model flat, c

.code

movdqa_test PROC xmm_reg_ptr:DWORD
  mov    eax,   xmm_reg_ptr
  movdqa xmm0,  [eax]
  movdqa xmm0,  [eax+1]	
  RET
movdqa_test ENDP


end
