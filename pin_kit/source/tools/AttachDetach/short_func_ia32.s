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


// This is a very short endless-loop function for 
// checking probe insertion and moving IP of thread that fails on probe

.type ShortFunc, @function
.global ShortFunc

ShortFunc:
.L:
push %eax
pop %eax
push %eax
pop %eax
nop
jmp .L

.type ShortFunc2, @function
.global ShortFunc2

ShortFunc2:
.L21:
test %eax, %eax
je .L22
push %eax
pop %eax
.L22:
jmp .L21
