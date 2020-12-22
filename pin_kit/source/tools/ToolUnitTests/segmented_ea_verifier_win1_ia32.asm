; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC TestSegmentedEA


.686
.model flat, c
COMMENT // use of segment register is not an ERROR
ASSUME NOTHING
.code
TestSegmentedEA PROC
    mov        eax, 18
    mov        ecx, 2
    mov        edx, DWORD PTR fs:[5]
    mov        DWORD PTR fs:[5], edx
    mov        edx, DWORD PTR fs:[eax]
    mov        DWORD PTR fs:[eax], edx
    mov        edx, DWORD PTR fs:[eax+5]
    mov        DWORD PTR fs:[eax+5], edx
    mov        edx, DWORD PTR fs:[ecx*2]
    mov        DWORD PTR fs:[ecx*2], edx
    mov        edx, DWORD PTR fs:[ecx*2+5]
    mov        DWORD PTR fs:[ecx*2+5], edx
    mov        edx, DWORD PTR fs:[eax+ecx]
    mov        DWORD PTR fs:[eax+ecx], edx
    mov        edx, DWORD PTR fs:[eax+ecx*2+5]
    mov        DWORD PTR fs:[eax+ecx*2+5], edx
    ret

TestSegmentedEA ENDP

end