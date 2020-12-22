; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.


PUBLIC GetIntegerScratches




.686
.XMM
.model flat, c

extern scratchVals:dword

.code

GetIntegerScratches PROC
    push esi
    lea esi, scratchVals
    mov dword ptr [esi], eax
    mov dword ptr [esi]+4, ecx
    mov dword ptr [esi]+8, edx
    pop esi
    ret
GetIntegerScratches ENDP

end