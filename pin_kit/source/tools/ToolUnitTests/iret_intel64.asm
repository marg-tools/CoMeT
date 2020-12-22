; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC iretTest
PUBLIC iret_func

.code

iret_func PROC
        mov rax,-2
        iretq

iret_func ENDP

iretTest PROC
        push    rbx
        ; Move the stack pointer down, so that we can check that the stack pointer
        ; is correctly restored by the iretq
        mov     rbx,rsp
        sub     rsp,80
        mov     rax,ss
        push    rax
        push    rbx    ; Restored stack pointer
        pushfq
        mov     rax,cs
        push    rax
        call    iret_func
        pop     rbx
        ret
iretTest ENDP

end
