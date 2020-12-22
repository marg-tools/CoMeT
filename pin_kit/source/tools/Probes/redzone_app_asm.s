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

#include "asm_macros.h"

#define REDZONE_SIZE 0x100

DECLARE_FUNCTION(CheckRedZone)
DECLARE_FUNCTION(InsideCheckRedZone)

.global NAME(CheckRedZone)
.global NAME(InsideCheckRedZone)

NAME(CheckRedZone):
	movq $REDZONE_SIZE/8, %rcx
	mov $0xdeadbeeffeedface, %rax
	lea -REDZONE_SIZE(%rsp), %rdi
	rep stosq
NAME(InsideCheckRedZone):
	movq $REDZONE_SIZE/8, %rcx
	mov $0xdeadbeeffeedface, %rax
	lea -REDZONE_SIZE(%rsp), %rdi
	repz scasq
	mov %rcx, %rax
	ret
