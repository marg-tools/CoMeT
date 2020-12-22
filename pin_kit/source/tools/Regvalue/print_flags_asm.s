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

DECLARE_FUNCTION(modifyFlags)

.global NAME(getFlags)
.global NAME(modifyFlags)

NAME(modifyFlags):
   ret

// Sets the flags register to the first argument of this function
// then call modifyFlags() and returns the value of the flags register
// after the invocation.
NAME(getFlags):
   BEGIN_STACK_FRAME
   pushf
   mov PARAM1, RETURN_REG
   push RETURN_REG
   popf
   call NAME(modifyFlags)
   pushf
   pop RETURN_REG
   popf
   END_STACK_FRAME
   ret

