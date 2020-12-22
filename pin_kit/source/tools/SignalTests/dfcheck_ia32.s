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
#if defined(TARGET_MAC)
.globl _DFSet
.globl _DidTest
.globl _Flags
#define DFSet _DFSet
#define DidTest _DidTest
#define Flags _Flags

.globl _SetAndClearDF
_SetAndClearDF:
#else
.globl SetAndClearDF
SetAndClearDF:
#endif
    std
    movl    $1, DFSet

    /*
     * Delay a little while to make it more likely that a signal
     * will arrive while DF is set.
     */
    mov     $0x1000, %eax
.L3:
    dec     %eax
    jne     .L3

    movl    $0, DFSet
    cld
    ret


    .align 4
#if defined(TARGET_MAC)
.globl _SignalHandler
_SignalHandler:
#else
.globl SignalHandler
SignalHandler:
#endif
    /*
     * Save the flags in 'Flags'.
     */
    pushf
    pop     %eax
    mov     %eax, Flags

    /*
     * The test is only interesting if the signal arrived while DF was
     * set (above in SetAndClearDF).
     */
    mov     DFSet, %eax
    mov     %eax, DidTest
    ret
