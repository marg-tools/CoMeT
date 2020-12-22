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

#
# Test for iretq in 64 bit mode.
# The code for iretd is commented out, since I haven't been able to find
# a coherent description of what it is supposed to do. (Working to the SDM description
# gives code that SEGVs)
#

# iretd_func:
#         mov $-1,%rax
#         .byte 0xcf

# .type iretdTest, @function
# .global iretdTest
# iretdTest:
#         # We have to build the stack frame ourselves
#         sub     $12,%rsp
#         mov     $-1, %rax
#         mov     %eax,8(%rsp)         #  Write the flags to one
#         mov     %cs, %rax
#         mov     %eax,4(%rsp)
#         lea     here,%rax
#         mov     %eax,0(%rsp)
#         jmp     iretd_func
# here:   
#         ret

iret_func:
        mov $-1,%rax
        iretq

#ifndef TARGET_MAC        
.type iretTest, @function
#endif
.global iretTest
iretTest:
        push    %rbx
        # Move the stack pointer down, so that we can check that the stack pointer
        # is correctly restored by the iretq
        mov     %rsp,%rbx
        sub     $80,%rsp
        mov     %ss,%rax
        push    %rax
        push    %rbx    # Restored stack pointer
        pushfq
        mov     %cs,%rax
        push    %rax
        call    iret_func
        pop     %rbx
        ret
        
