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

// This function is never called

DECLARE_FUNCTION(foo)
DECLARE_FUNCTION(bar)

NAME(foo):
	BEGIN_STACK_FRAME
        END_STACK_FRAME
        call *GAX_REG
END_FUNCTION(foo)

        .byte   0x0

NAME(bar):
        BEGIN_STACK_FRAME
        mov $0x1ee7,RETURN_REG
        END_STACK_FRAME
        ret
END_FUNCTION(bar)
