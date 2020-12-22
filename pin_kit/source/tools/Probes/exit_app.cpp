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
#include <stdlib.h>

void bye1() 
{
    printf("That was all, folks - 1\n");\
}
void bye2() 
{
    printf("That was all, folks - 2\n");\
}


int main()
{
    int res = atexit(bye1);
    if (res != 0)
    {
        fprintf(stderr, "cannot set exit function\n");
        return EXIT_FAILURE;           
    }
    res = atexit(bye2);
    if (res != 0)
    {
        fprintf(stderr, "cannot set exit function\n");
        return EXIT_FAILURE;           
    }
    return EXIT_SUCCESS;
}
