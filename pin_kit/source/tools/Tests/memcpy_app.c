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

#include <string.h>

int main()
{
    char buff0[100];
    char buff1[]="My buffer source";

    memcpy(&buff0[0],&buff1[0],strlen(buff1));
    memcpy(&buff0[0],&buff1[0],strlen(buff1));

    memmove(&buff0[0],&buff1[0],strlen(buff1));
    memmove(&buff0[0],&buff1[0],strlen(buff1));

    return 0;
}
