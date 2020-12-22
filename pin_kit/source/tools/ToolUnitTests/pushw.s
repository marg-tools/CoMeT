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

.global pushIW_
.type pushIW_, function
pushIW_:      
	mov     %esp, %ecx      # Save esp
	mov     4(%esp),%esp    # stack to play with
	pushw   $-5             # Do the op
	mov     %esp, %eax      # Result
	mov     %ecx, %esp      # Stack with return address
	ret
