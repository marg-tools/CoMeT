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

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

static void *child(void *);
static void *parent(void *);


int main()
{
    pthread_t tid;
    if (pthread_create(&tid, 0, child, 0) != 0)
        return 1;
    parent(0);

    pthread_join(tid, 0);
    printf(" test complete\n");
    return 0;
}


static void *child(void *dummy)
{
    malloc(1);
    return 0;
}

static void *parent(void *dummy)
{
    malloc(1);
    return 0;
}
