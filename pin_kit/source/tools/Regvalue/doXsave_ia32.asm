; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC DoXsave

.686
.XMM
.model flat, c
extern xsaveArea:dword
extern flags:dword

.code

; void DoXsave();
; This function calls xsave and stores the FP state in the given dst area.
; The caller is expected to allocate enough space for the xsave area.
; The function expects the given dst pointer to be properly aligned for the xsave instruction.
DoXsave PROC

    mov     eax, [flags]
    lea     ecx, xsaveArea
    xor     edx, edx

    ; Do xsave
    xsave   [ecx]

    ret
DoXsave ENDP

; void DoXsaveOpt();
; This function calls xsaveopt and stores the FP state in the given dst area.
; The caller is expected to allocate enough space for the xsaveopt area.
; The function expects the given dst pointer to be properly aligned for the xsaveopt instruction.
DoXsaveOpt PROC

    mov     eax, [flags]
    lea     ecx, xsaveArea
    xor     edx, edx

    ; Do xsave
    xsaveopt   [ecx]

    ret
DoXsaveOpt ENDP

; void DoXrstor();
; This function calls xrstor and restores the specified thetures from the xsave dst area.
; The function expects the given dst pointer to be properly aligned
DoXrstor PROC

    mov     eax, [flags]
    lea     ecx, xsaveArea
    xor     edx, edx

    ; Do xrstor
    xrstor   [ecx]

    ret
DoXrstor ENDP

; void DoFxsave();
; This function calls fxsave and stores the legacy FP state in the given dst area.
; The caller is expected to allocate enough space for the xsave area.
; The function expects the given dst pointer to be properly aligned for the fxsave instruction.
DoFxsave PROC

    lea     ecx, xsaveArea

    ; Do fxsave
    fxsave   [ecx]

    ret
DoFxsave ENDP

; void Dofxrstor();
; This function calls fxrstor and restores legacy state from the xsave dst area.
; The function expects the given dst pointer to be properly aligned
DoFxrstor PROC

    lea     ecx, xsaveArea

    ; Do fxrstor
    fxrstor   [ecx]

    ret
DoFxrstor ENDP


end
