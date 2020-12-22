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
.globl One
One:
    /*
     * The debugger stops at a breakpoint here and then changes the PC to &Two().
     */
    movl    $1, %eax
    ret


.globl Two
Two:
    movl    $2, %eax
    ret


.globl GetValue
GetValue:
    /*
     * Call indirect here so that the breakpoint is hit after an indirect jump.
     */
    mov     4(%esp), %eax
    call    *%eax
    ret
