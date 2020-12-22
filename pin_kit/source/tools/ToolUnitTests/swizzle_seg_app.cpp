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

extern "C" int SegAccessRtn(int val);
extern "C" int SegAccessStrRtn(int val);
int main()
{
    int value;
    if ((SegAccessRtn(5) != 105) || (SegAccessRtn(6) != 106))
    {
        fprintf(stderr, "SegAccessRtn failed\n");
        return -1;
    }
    printf("SegAccessRtn success\n");
	
    value = SegAccessStrRtn(30);
    if (value != 30)
    {
        fprintf(stderr, "SegAccessStrRtn failed (%d, not 30)\n", value);
        return -1;
    }
    printf("SegAccessStrRtn success\n");
	
    return 0;
	
}

	
	
