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
#include <errno.h>

main()
{
    int fd[2];
    ssize_t sz;
    char buf[80];


    printf("This is pid %d\n", (int)getpid());

    pipe(fd);
    sz = read(fd[0], buf, sizeof(buf));

    printf("sz = %d\n", (int)sz);
    if (sz == -1)
        printf("errno = %d\n", errno);
    return 0;
}
