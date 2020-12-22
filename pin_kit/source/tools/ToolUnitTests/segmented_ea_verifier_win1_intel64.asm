; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC TestSegmentedEA


.code
TestSegmentedEA PROC
    mov        rax, 18
    mov        rcx, 2
    mov        rdx, QWORD PTR gs:[5]
    mov        QWORD PTR gs:[5], rdx
    mov        rdx, QWORD PTR gs:[rax]
    mov        QWORD PTR gs:[rax], rdx
    mov        rdx, QWORD PTR gs:[rax+5]
    mov        QWORD PTR gs:[rax+5], rdx
    mov        rdx, QWORD PTR gs:[rcx*2]
    mov        QWORD PTR gs:[rcx*2], rdx
    mov        rdx, QWORD PTR gs:[rcx*2+5]
    mov        QWORD PTR gs:[rcx*2+5], rdx
    mov        rdx, QWORD PTR gs:[rax+rcx]
    mov        QWORD PTR gs:[rax+rcx], rdx
    mov        rdx, QWORD PTR gs:[rax+rcx*2+5]
    mov        QWORD PTR gs:[rax+rcx*2+5], rdx
    ret

TestSegmentedEA ENDP

end
