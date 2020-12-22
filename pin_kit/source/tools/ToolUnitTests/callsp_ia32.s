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
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp

    /*
     * Push a 'ret' instruction, then call it.
     */
    pushl   $0xc3       /* ret */
	call	*%esp
    popl    %eax

    /*
     * Push a 'jmp *%ecx' instruction, then jump to it.
     */
    lea     .l1, %ecx
    pushl   $0xe1ff     /* jmp *%ecx */
    jmp     *%esp
.l1:
    popl    %eax

	xorl	%eax, %eax
	leave
	ret
