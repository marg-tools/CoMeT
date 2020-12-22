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
.globl foo
foo:
    pushl   %ebp        /* BP here and ... */
    movl    %esp, %ebp  /* ... here, to test for BP's on adjacent instructions */
    subl    $8, %esp
    call    sub
    call    sub
    leave               /* BP here to test BP on target of indirect jump */
    ret

.globl sub
sub:
    ret                 /* BP here to test BP on indirect jump */
