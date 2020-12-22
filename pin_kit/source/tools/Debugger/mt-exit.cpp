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
#include <unistd.h>
#include <pthread.h>

static void *Blocker(void *);
static void Breakpoint();


int main()
{
    pthread_t tid;
    if (pthread_create(&tid, 0, Blocker, 0) != 0)
    {
        std::cerr << "Unable to create thread\n";
        return 1;
    }

    // Wait for the child process to block in its sleep() call,
    // and then trigger the breakpoint.
    //
    sleep(5);
    Breakpoint();

    pthread_join(tid, 0);
    return 0;
}


static void *Blocker(void *)
{
    sleep(1000);
    return 0;
}

static void Breakpoint()
{
    // GDB places a breakpoint here and then terminates
    // the application.
}
