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



.global SegAccessRtn
.type SegAccessRtn, @function

SegAccessRtn:

push %rbp
mov %rsp, %rbp
push %rcx

mov %rdi, %fs:0x10
mov %fs:0x10, %rax

mov $0x10, %rcx
mov %fs:0(%rcx), %rax

movl $100, %fs:0x14
mov $0x10, %rcx
addq %fs:4(%rcx), %rax

pop %rcx
leave
ret

//int SegAccessStrRtn(int x)

.global SegAccessStrRtn
.type SegAccessStrRtn, @function

SegAccessStrRtn:

push %rbp
mov %rsp, %rbp


movq %rdi, %fs:0x14
mov $0x14, %rsi

lodsq %fs:(%rsi), %rax

leave
ret


