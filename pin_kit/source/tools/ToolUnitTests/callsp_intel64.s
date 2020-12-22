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

/*
 * This test verifies Pin's handling of two weird instructions:
 * "call *%rsp" and "jmp *%rsp".
 */

	.text
.globl main
main:
	subq	$8, %rsp

    /*
     * Push a 'ret' instruction, then call it.
     */
    pushq   $0xc3       /* ret */
	call	*%rsp
    popq    %rax

    /*
     * Push a 'jmp *%rcx' instruction, then jump to it.
     */
    lea     .l1(%rip), %rcx
    pushq   $0xe1ff     /* jmp *%rcx */
    jmp     *%rsp
.l1:
    popq    %rax

	xorl	%eax, %eax
	addq	$8, %rsp
	ret
