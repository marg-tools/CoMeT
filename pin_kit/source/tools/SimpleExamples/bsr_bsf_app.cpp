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
#include <string.h>

extern "C" int bsr_func(int);
extern "C" int bsf_func(int);

int main()
{
    // Call 'bsr_func' and 'bsf_func' implemented in assembly
    printf("BSR of 0 is %d\n", bsr_func(0));
    printf("BSR of 888 is %d\n", bsr_func(888));
    printf("BSF of 0 is %d\n", bsf_func(0));
    printf("BSF of 888 is %d\n", bsf_func(888));
    return 0;
}
