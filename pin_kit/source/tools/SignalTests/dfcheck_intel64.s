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
    .align 4
.globl SetAndClearDF
SetAndClearDF:
    std
    movl    $1, DFSet(%rip)

    /*
     * Delay a little while to make it more likely that a signal
     * will arrive while DF is set.
     */
    mov     $0x1000, %eax
.L3:
    dec     %eax
    jne     .L3

    movl    $0, DFSet(%rip)
    cld
    ret


    .align 4
.globl SignalHandler
SignalHandler:
    /*
     * Save the flags in 'Flags'.
     */
    pushf
    pop     %rax
    mov     %eax, Flags(%rip)

    /*
     * The test is only interesting if the signal arrived while DF was
     * set (above in SetAndClearDF).
     */
    mov     DFSet(%rip), %eax
    mov     %eax, DidTest(%rip)
    ret
