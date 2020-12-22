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
#if defined(TARGET_MAC)
.globl _DoMath
_DoMath:
#else
.globl DoMath
DoMath:
#endif
    /*
     * Push "0.0" on the stack, then "1.0".
     */
    finit
    fldz
    fld1

    /*
     * This raises a SEGV.
     */
    mov     $0, %ecx
    mov     (%ecx), %ecx

    /* does not return */
	ret
