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

#ifdef TARGET_MAC
#define NAME(x) _##x
#else
#define NAME(x) x
#endif

// This assembly file should built to an executable file
// It tests the correctness of jcxz instruction and exits
// with status 0 if everything's OK.

.global NAME(main)

NAME(main):
   mov $0x10000, %ecx
   xor %eax,%eax
   jcxz test_pass
   mov $1, %al
test_pass:
   ret

