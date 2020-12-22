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

extern xsaveArea:dword

.code
Do_Fxsave PROC
    lea    GCX_REG, xsaveArea
    fxsave [GCX_REG]
    ret
Do_Fxsave ENDP

.code
Do_Fxrstor PROC
    lea     GCX_REG, xsaveArea
    fxrstor [GCX_REG]
    fxrstor  [xsaveArea]
    ret
Do_Fxrstor ENDP

end
