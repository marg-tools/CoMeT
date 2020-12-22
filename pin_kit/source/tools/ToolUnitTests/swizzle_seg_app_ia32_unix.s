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

push %ebp
mov %esp, %ebp
push %ecx

mov 0x8(%ebp), %eax
mov %eax, %gs:0x10
mov %gs:0x10, %eax

mov $0x10, %ecx
mov %gs:0(%ecx), %eax

movl $100, %gs:0x14
mov $0x10, %ecx
addl %gs:4(%ecx), %eax

pop %ecx
leave
ret

//int SegAccessStrRtn(int x)

.global SegAccessStrRtn
.type SegAccessStrRtn, @function

SegAccessStrRtn:

push %ebp
mov %esp, %ebp

mov 0x8(%ebp), %eax

movl %eax, %gs:0x14
mov $0x14, %esi

lodsl %gs:(%esi), %eax

leave
ret


