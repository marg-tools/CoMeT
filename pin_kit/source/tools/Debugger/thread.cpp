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

#include <iostream>
#include <cstdlib>
#include <pthread.h>

static void *child(void *);
static void *parent(void *);


int main()
{
    pthread_t tid;
    if (pthread_create(&tid, 0, child, 0) != 0)
        std::cerr << "Unable to create thread\n";
    parent(0);

    pthread_join(tid, 0);
    return 0;
}


static void *child(void *)
{
    malloc(1);
    std::cout << "This is the child\n";
    return 0;
}

static void *parent(void *)
{
    malloc(1);
    std::cout << "This is the parent\n";
    return 0;
}
