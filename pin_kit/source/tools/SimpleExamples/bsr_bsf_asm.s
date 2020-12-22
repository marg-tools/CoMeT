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

DECLARE_FUNCTION(bsr_func)
DECLARE_FUNCTION(bsf_func)

.global NAME(bsr_func)
.global NAME(bsf_func)
//.intel_syntax noprefix 

// int bsr_func(int src) - this function returns the bit index of the 
// most significant bit set. in case 'src' is zero, -1 is returned.
NAME(bsr_func):
   BEGIN_STACK_FRAME
   mov $0, RETURN_REG
   not RETURN_REG
   bsr PARAM1, RETURN_REG
   END_STACK_FRAME
   ret

// int bsr_func(int src) - this function returns the bit index of the 
// least significant bit set. in case 'src' is zero, -1 is returned.
NAME(bsf_func):
   BEGIN_STACK_FRAME
   mov $0, RETURN_REG
   not RETURN_REG
   bsf PARAM1, RETURN_REG
   END_STACK_FRAME
   ret

