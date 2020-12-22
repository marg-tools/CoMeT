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
#include <unistd.h>


int main()
{
    int fd[2];

    if (pipe(fd) != 0)
    {
        fprintf(stderr, "pipe failed\n");
        return 1;
    }

    printf("Pipe returned file descriptors: %d, %d\n", fd[0], fd[1]);

    if (close(fd[0]) != 0)
    {
        fprintf(stderr, "File descriptor %d is invalid\n", fd[0]);
        return 1;
    }
    if (close(fd[1]) != 0)
    {
        fprintf(stderr, "File descriptor %d is invalid\n", fd[1]);
        return 1;
    }

    return 0;
}
