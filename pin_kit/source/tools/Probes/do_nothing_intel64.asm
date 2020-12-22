; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.


COMMENT // contains important code patterns
COMMENT // doesn't actually do anything
COMMENT // make sure the relocated entry will copy more than one basic block.

.code
PUBLIC do_nothing
do_nothing PROC

    test rax, rax
    je lab1

    xor rax, rax
    xor rax, rax

lab1:
    xor rax, rax
    xor rax, rax

    ret
do_nothing ENDP

COMMENT // make sure the relocated entry will correctly handle a jump as the last
COMMENT // instruction in the basic block.

PUBLIC nothing_doing
nothing_doing PROC
    test rax, rax
    test rax, rax
    je lab2

    xor rax, rax
    xor rax, rax

lab2:
    xor rax, rax
    xor rax, rax

    ret
nothing_doing ENDP

COMMENT // call should be replaced with a push/jmp when relocated.

PUBLIC call_function
call_function PROC

    push rbx
    call do_nothing
    pop rbx
    ret
call_function ENDP

COMMENT // make sure this code pattern works

PUBLIC call_nothing
call_nothing PROC
    push rax
    mov  rax, rax
    push rbx
    call do_nothing
    pop  rbx
    pop  rax
    ret
call_nothing ENDP

END
