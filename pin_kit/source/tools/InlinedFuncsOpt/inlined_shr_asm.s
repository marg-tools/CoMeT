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

DECLARE_FUNCTION(Proc1)
.global NAME(Proc1)	

NAME(Proc1): 
 mov GAX_REG, GCX_REG
 shl CL_REG, GDX_REG
 ret 

