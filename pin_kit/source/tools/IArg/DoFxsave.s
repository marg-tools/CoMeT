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

.data
.extern xsaveArea


.text

DECLARE_FUNCTION_AS(Do_Fxsave)
Do_Fxsave:
    lea     PIC_VAR(xsaveArea), GCX_REG
    fxsave (GCX_REG)
    ret
END_FUNCTION(Do_Fxsave)
    
DECLARE_FUNCTION_AS(Do_Fxrstor)
Do_Fxrstor:
    lea     PIC_VAR(xsaveArea), GCX_REG
    fxrstor (GCX_REG)
    ret
END_FUNCTION(Do_Fxrstor)
