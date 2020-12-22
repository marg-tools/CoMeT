; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC GetConsts




extern uint32Glob:qword
extern addrIntGlob:qword
.code
GetConsts PROC
    mov r8, rcx
    lea r9, uint32Glob
    mov QWORD PTR [r9], r8
    mov r10, rdx
    lea r11, addrIntGlob
    mov QWORD PTR [r11], r10
    ret


GetConsts ENDP



end