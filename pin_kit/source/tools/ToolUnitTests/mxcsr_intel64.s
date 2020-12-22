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

.text
#ifdef TARGET_MAC
.globl _GetMxcsr
_GetMxcsr:
#else
.globl GetMxcsr
.type GetMxcsr, function
GetMxcsr: 
#endif
	stmxcsr (%rdi)
    ret


#ifdef TARGET_MAC
.globl _SetMxcsr
_SetMxcsr:
#else
.globl SetMxcsr
.type SetMxcsr, function
SetMxcsr: 
#endif
	ldmxcsr (%rdi)
    ret
 
