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

.intel_syntax noprefix
	
	.data
	.align 16
a1:		
	.long 0xdeadbeef
	.long 0xfeedfeed
.text
.globl clobberRegs
.type clobberRegs, function
clobberRegs:
	mov rax, 0xdeadbeef
	mov rcx, 0xdeadbeef
	mov rdx, 0xdeadbeef
	mov rsi, 0xdeadbeef
	mov rdi, 0xdeadbeef
	mov r8, 0xdeadbeef
	mov r9, 0xdeadbeef
	mov r10, 0xdeadbeef
	mov r11, 0xdeadbeef
	movaps xmm0,[rip+a1]
	# to prevent the clobbers from being optimized
	add rax, rcx
	add rax, rdx
	add rax, rsi
	add rax, rdi
	add rax, r8
	add rax, r9
	add rax, r10
	add rax, r11
	ret
	
