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

# this code pattern tests an ip-relative displacement
# on a call instruction in the probe area.
	
    .text
.globl Bar
    .type   Bar, @function
Bar:
    pushq   %rbp
    movq    %rsp, %rbp
    leave
    ret

.globl pf
    .text
    .align 8
    .type   pf, @object
    .size   pf, 8
pf:
    .quad   Bar

    .text
.globl Foo
    .type   Foo, @function
Foo:
    pushq   %rbp
    movq    %rsp, %rbp

    call    *(pf-.-6)(%rip)  # 6 = size of this call instruction

    leave
    ret
	
# this code pattern tests an ip-relative jmp in the probe area.
	
.globl pt
    .text
    .align 8
    .type   pt, @object
    .size   pt, 8
pt:
    .quad   Bar

    .text
.globl Haha
    .type   Haha, @function
Haha:
    jmp    *(pt-.-6)(%rip)  # 6 = size of this instruction
