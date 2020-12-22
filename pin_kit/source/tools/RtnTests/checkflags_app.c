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

#include <stdio.h>

extern int CheckFlags(unsigned int*, unsigned int*);

int main()
{
    unsigned int before = 0;
    unsigned int after = 0;
    if (0 != CheckFlags(&before, &after))
    {
        fprintf(stderr, "APP ERROR: Flags register was corrupted: before 0x%x, after 0x%x\n", before, after);
        return 1;
    }
    return 0;
}
