; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

.code
SetMxcsr PROC
    push    rcx
    ldmxcsr [rsp]
    pop     rcx
    ret
SetMxcsr ENDP

GetMxcsr PROC
    push    rax
    stmxcsr [rsp]
    pop     rax
    ret
GetMxcsr ENDP

end
