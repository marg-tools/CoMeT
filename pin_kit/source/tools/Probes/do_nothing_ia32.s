/*
 * Copyright 2002-2019 Intel Corporation.
 * 
 * This software is provided to you as Sample Source Code as defined in the accompanying
 * End User License Agreement for the Intel(R) Software Development Products ("Agreement")
 * section 1.L.
 * 
 * This software and the related documents are provided as is, with no express or implied
 * warranties, other than those that are expressly stated in the License.
 */

#include <asm_macros.h>

# 
# contains important code patterns
# doesn't actually do anything

# make sure the relocated entry will copy more than one basic block.
.text
.global NAME(do_nothing)
DECLARE_FUNCTION(do_nothing)

NAME(do_nothing):
    test %eax, %eax
    je lab1

    xor %eax, %eax
    xor %eax, %eax

lab1:
    xor %eax, %eax
    xor %eax, %eax

    ret

#make sure the relocated entry will correctly handle a jump as the last
#instruction in the basic block.
.global NAME(nothing_doing)
DECLARE_FUNCTION(nothing_doing)

NAME(nothing_doing):
    test %eax, %eax
    test %eax, %eax
    je lab2

    xor %eax, %eax
    xor %eax, %eax

lab2:
    xor %eax, %eax
    xor %eax, %eax

    ret

# call should be replaced with a push/jmp when relocated.
#
.global NAME(call_function)
DECLARE_FUNCTION(call_function)

NAME(call_function):
    push %ebx
    call NAME(do_nothing)
    pop %ebx
    ret


# make sure this code pattern works
#
.global NAME(call_nothing)
DECLARE_FUNCTION(call_nothing)

NAME(call_nothing):
    push %eax
    mov %eax, %eax
    push %ebx
    call NAME(do_nothing)
    pop %ebx
    pop %eax
    ret


