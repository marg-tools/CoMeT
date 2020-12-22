; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC SetAppFlags_asm
PUBLIC ClearAcFlag_asm
PUBLIC GetFlags_asm




.code
SetAppFlags_asm PROC
    pushfq
    pop rax
    or rax, rcx
    push rax
    popfq
    ret


SetAppFlags_asm ENDP

ClearAcFlag_asm PROC   
    pushfq
    pop rcx
    and rcx, 0fffbffffH
    push rcx
    popfq
    ret

ClearAcFlag_asm ENDP
GetFlags_asm PROC
    pushfq
    pop rax
    ret
GetFlags_asm ENDP

end