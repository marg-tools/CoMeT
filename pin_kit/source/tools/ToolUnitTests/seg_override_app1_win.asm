; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC TestSegOverride


.686
.model flat, c
extern source:word
extern dest:word
COMMENT // use of segment register is not an ERROR
ASSUME NOTHING
.code
TestSegOverride PROC
    push       esi
    push       edi
    lea        esi, source
    lea        edi, dest
    push       fs
    push       es
    pop        fs
    mov        eax, DWORD PTR fs:[esi]
    pop        fs
    mov        DWORD PTR [edi], eax
    mov        eax, DWORD PTR fs:[0]
    add        esi, 4
    add        edi, 4 
    mov        eax, DWORD PTR [esi]
    mov        DWORD PTR [edi], eax
    pop        edi
    pop        esi
    ret

TestSegOverride ENDP

end