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

extern int my_yield();

int my_marker()
{
    return 1;
}

int main()
{
    int i;

    printf("Calling my_yield()\n");

    for (i = 0; i < 100; i++)
    {
        int res = my_yield();
        if (res != 0)
        {
            printf("my_yield failed...\n");
            exit(1);
        }
    }

    my_marker();

    return(0);
}
