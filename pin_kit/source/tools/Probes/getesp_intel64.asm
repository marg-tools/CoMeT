; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC GetEspBeforeCalled


.code

GetEspBeforeCalled PROC
    mov        rax, rsp
    add        rax, 8
    ret  
GetEspBeforeCalled ENDP
    


end