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

.global Do32BitOverride
.type Do32BitOverride, @function
Do32BitOverride:
           mov  (%rsi),    %rax
    addr32 movl  %eax,      (%edi)
           lea   0x8(%rsi), %rsi
    addr32 lea   0x8(%edi), %edi
    addr32 movsl
           lea   0x4(%rsi), %rsi
    addr32 lea   0x4(%edi), %edi 
           push  (%rsi)
    addr32 pop   (%edi)
    addr32 push  (%edi)
    addr32 lea   0xc(%edi), %edi
    addr32 pop   (%edi)
    ret
