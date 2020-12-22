; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC GetIntegerScratches




extern scratchVals:dword

.code





GetIntegerScratches PROC
    push rsi
    lea rsi, scratchVals
    mov qword ptr [rsi], rax
    mov qword ptr [rsi]+8, rcx
    mov qword ptr [rsi]+16, rdx
    mov qword ptr [rsi]+24, r8
    mov qword ptr [rsi]+32, r9
    mov qword ptr [rsi]+40, r10
    mov qword ptr [rsi]+48, r11
    pop rsi
    ret
GetIntegerScratches ENDP

end
