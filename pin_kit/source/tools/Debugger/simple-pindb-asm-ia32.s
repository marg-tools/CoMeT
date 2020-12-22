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
.globl Breakpoint
Breakpoint:
    nop
.globl Breakpoint2
Breakpoint2:
    ret

    .data
.globl MemTestData
MemTestData:
    .long 0x12345678
    .long 0xdeadbeef

    .text
.globl DoRegMemTest
DoRegMemTest:
    lea     MemTestData, %eax
    mov     (%eax), %ecx
    mov     %ecx, (%eax)
    ret

    .text
.globl DoStepCustomBreakTest
DoStepCustomBreakTest:
    nop
    call    Breakpoint
    ret
