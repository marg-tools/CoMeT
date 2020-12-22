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
    mov        $0x18, %eax
    mov        $4,  %ecx
    mov        %gs:0x10, %edx
    mov        %edx, %gs:0x10
	mov        %gs:0(%eax), %edx
	mov        %edx, %gs:0(%eax)
	mov        %gs:4(%eax), %edx
	mov        %edx, %gs:4(%eax)
	mov        %gs:4(%eax, %ecx, 1), %edx
	mov        %edx, %gs:4(%eax, %ecx, 1)
	mov        %gs:0(%eax, %ecx, 1), %edx
	mov        %edx, %gs:0(%eax, %ecx, 1)
	mov        %gs:0(, %ecx, 1), %edx
	mov        %edx, %gs:0(, %ecx, 1)
    ret



