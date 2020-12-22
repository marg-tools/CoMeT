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

// Verify that Pin does not crash if the application terminates with a
// fatal synchronous signal.

int main()
{
    int *p = (int *)0x9;
    *p = 8;
    return 0;
}
