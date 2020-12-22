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

.global MovsTest
.type MovsTest, @function

MovsTest:
push %ebp
mov %esp, %ebp
mov 0x8(%ebp), %esi
mov 0xc(%ebp), %edi
movsl %fs:(%esi), %es:(%edi)
mov %es:-4(%edi), %eax
leave
ret

.global MaskMovqTest
.type MaskMovqTest, @function

MaskMovqTest:
push %ebp
mov %esp, %ebp
mov 0x8(%ebp), %edi    # first operand - an offset under fs
mov 0xc(%ebp), %esi    # second operand - the number to be copied
movl $0xffffffff, %eax
movd %eax, %xmm0       # mask
movd %esi, %xmm1       # the number to be copied
.byte 0x64
maskmovdqu %xmm0, %xmm1
leave
ret

.global PushPopTest
.type PushPopTest, @function

PushPopTest:
push %ebp
mov %esp, %ebp
mov 0x8(%ebp), %edi    # first operand - an offset under fs
mov 0xc(%ebp), %esi    # second operand - the number to be copied
mov %esi, %fs:(%edi)
push %fs:(%edi)
addl $4, %edi
pop %fs:(%edi)
mov %fs:(%edi), %eax
leave
ret

.global CallTest
.type CallTest, @function

CallTest:
push %ebp
mov %esp, %ebp
mov 0x8(%ebp), %edi    # first operand - an offset under fs
call *%fs:(%edi)
leave
ret

