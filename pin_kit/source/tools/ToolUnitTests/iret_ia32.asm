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

.686
.XMM
.model flat,c
.code

iret_func PROC
        mov eax,-1
        iretd

iret_func ENDP

iretTest PROC
        ; We have to build the stack frame ourselves
        sub     esp,12
        mov     eax,0
        mov     [esp+8],eax         ; Write the flags to zero
        mov     eax,cs
        mov     [esp+4],eax
        lea     eax,here
        mov     [esp+0],eax
        jmp     iret_func
here:   
        ret
iretTest ENDP

end
