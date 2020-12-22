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
    .globl func_is_5

# Return 1 if function argument equals to 5, Return 0 othersize.
# --- func_is_5(int)
func_is_5:
# parameter 1: %edi
L1:
        # 67H prefix (Address-size override prefix) which mean use low 32 bit of RIP
        # Copy 5 to RAX
        .byte 0x67
        movq      var@GOTPCREL(%rip), %rax
        movl      (%rax), %edx
        xorl      %eax, %eax
        cmpl      %edx, %edi
        sete      %al
        ret
L2:
    .type   func_is_5,@function
    .size   func_is_5,.-func_is_5
    .data
# -- End  func_is_5
    .data
    .align 4
    .globl var
var:
    .long   5
    .type   var,@object
    .size   var,4

    .globl func_is_5_size
func_is_5_size:
    .long   L2-L1
    .type   func_is_5_size,@object
    .size   func_is_5_size,4



