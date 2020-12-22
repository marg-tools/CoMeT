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

#include <asm_macros.h>
#include <asm/unistd.h>

DECLARE_FUNCTION(_start)

NAME(_start):
    BEGIN_STACK_FRAME
    add $100, STACK_PTR
    PREPARE_UNIX_SYSCALL($__NR_exit_group)
    mov $0, SYSCALL_PARAM1
    INVOKE_SYSCALL
    END_STACK_FRAME
    ud2

.section .data, "aw"
.byte 1
