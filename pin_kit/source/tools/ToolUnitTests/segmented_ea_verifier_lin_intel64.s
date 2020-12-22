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

.global TestSegmentedEA
.type TestSegmentedEA, @function


// use of segment register is not an ERROR


TestSegmentedEA:
    push       %rdx
    push       %rcx
    mov        $0x18, %rax
    mov        $8,  %rcx
    mov        %fs:0x10, %rdx
    mov        %rdx, %fs:0x10
	mov        %fs:0(%rax), %rdx
	mov        %rdx, %fs:0(%rax)
	mov        %fs:4(%rax), %rdx
	mov        %rdx, %fs:4(%rax)
	mov        %fs:4(%rax, %rcx, 1), %rdx
	mov        %rdx, %fs:4(%rax, %rcx, 1)
	mov        %fs:0(%rax, %rcx, 1), %rdx
	mov        %rdx, %fs:0(%rax, %rcx, 1)
	mov        %fs:0(, %rcx, 1), %rdx
	mov        %rdx, %fs:0(, %rcx, 1)
	pop        %rcx
	pop        %rdx
    ret



