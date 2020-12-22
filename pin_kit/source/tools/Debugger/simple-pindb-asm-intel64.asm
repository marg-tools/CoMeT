; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC Breakpoint
PUBLIC Breakpoint2
PUBLIC MemTestData
PUBLIC DoRegMemTest


.code
Breakpoint PROC
    nop
Breakpoint2::
    ret
Breakpoint ENDP


.data
MemTestData DWORD 012345678h, 0deadbeefh


.code
DoRegMemTest PROC
    lea     rax, MemTestData
    mov     ecx, DWORD PTR [rax]
    mov     DWORD PTR [rax], ecx
    ret
DoRegMemTest ENDP

.code
DoStepCustomBreakTest PROC
    nop
    call    Breakpoint
    ret
DoStepCustomBreakTest ENDP

END
