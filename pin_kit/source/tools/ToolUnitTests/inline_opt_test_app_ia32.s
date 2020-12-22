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

.global scratchVals

.text
.global GetIntegerScratches
.type GetIntegerScratches,  @function
GetIntegerScratches:
    push %esi
    lea scratchVals, %esi
    mov %eax, (%esi)
    mov %ecx, 0x4(%esi)
    mov %edx, 0x8(%esi)
    pop %esi
    ret
