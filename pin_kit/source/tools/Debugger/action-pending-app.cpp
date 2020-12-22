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

/*
 * This test application is only interesting when run with the tool
 * "action-pending-tool.cpp".  When run under the debugger, it tests the
 * PIN_IsActionPending() API.
 */

#include <iostream>
#include <pthread.h>
#include <unistd.h>

static void *Child(void *);
static void Parent();
extern "C" void Breakpoint();
extern "C" void ToolWait();
extern "C" void ToolSignal();


int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid, 0, Child, 0);
    if (ret != 0)
    {
        std::cerr << "Unable to create thread" << std::endl;
        return 1;
    }

    Parent();

    pthread_join(tid, 0);
    return 0;
}

static void *Child(void *)
{
    ToolWait();
    return 0;
}

static void Parent()
{
    sleep(2);       /* wait for Child to call ToolWait() */
    Breakpoint();
    ToolSignal();
}

extern "C" void Breakpoint()
{
    /* debugger sets a breakpoint here */
}

extern "C" void ToolWait()
{
    /* Pin tool adds analysis routine here to wait for ToolSignal() */
}

extern "C" void ToolSignal()
{
    /* Pin tool adds analysis routine here to release ToolWait() */
}
