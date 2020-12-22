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
# Test for iret in 32 bit mode.
#

iret_func:
        mov $-1,%eax
        iret

#ifndef TARGET_MAC
.type iretTest, @function
#endif
.global iretTest
iretTest:
        # We have to build the stack frame ourselves
        sub     $12,%esp
        mov     $0, %eax
        mov     %eax,8(%esp)         #  Write the flags to zero
        mov     %cs, %eax
        mov     %eax,4(%esp)
        lea     here,%eax
        mov     %eax,0(%esp)
        jmp     iret_func
here:   
        ret

