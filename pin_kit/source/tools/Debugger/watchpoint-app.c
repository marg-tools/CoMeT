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


int A[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int Sum = 0;

int main(int argc, char **argv)
{
    int i;

    /*
     * If there's an argument, print the debugger commands.
     */
    if (argc > 1)
    {
        printf("monitor watch 0x%lx\n", (long)&Sum);
        printf("c\n");
        printf("p Sum\n");
        printf("c\n");
        printf("p Sum\n");
        printf("c\n");
        printf("p Sum\n");
        printf("c\n");
        printf("p Sum\n");
        printf("q\n");
        return 0;
    }

    printf("Hello world\n");
    for (i = 0;  i < 10;  i++)
        Sum += A[i];

    printf("Sum is %d\n", Sum);
    return 0;
}
