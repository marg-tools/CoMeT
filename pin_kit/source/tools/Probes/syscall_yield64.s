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

# this routine calls a system call in the first bytes of the function
# within the probe space.
#
.text
.global my_yield
.type my_yield, function

my_yield:
    mov    $0x18,%eax   # this is the number of SYS_sched_yield
    syscall
    cmp    $0xfffffffffffff001,%rax
    jae    .fail
    retq
.fail:
    or     $0xffffffffffffffff,%rax
    retq

