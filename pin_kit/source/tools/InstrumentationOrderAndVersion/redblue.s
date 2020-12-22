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
.globl main
.type main, function
main:	
	mov eax,0
	cmp eax,0
	call red
	call blue
	mov eax,1
	cmp eax,0
	call red
	call blue
	mov eax,0
	ret
	
.globl red
.type red, function
red:		
	jz r2
	jmp common
r2:
	jmp common
	
.globl blue
.type blue, function
blue:		
	jz b2
	jmp common
b2:	
	jmp common	
.globl common
.type common, function
common:		
	ret
						
