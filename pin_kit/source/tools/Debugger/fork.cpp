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

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void DoChild();
static void DoCommon();

int main()
{
    pid_t pid = fork();
    if (pid != 0)
        waitpid(pid, 0, 0);
    else
        DoChild();
    DoCommon();
    return 0;
}


int Glob = 0;

static void DoChild()
{
    Glob++;
}

static void DoCommon()
{
    /* debugger places a breakpoint here */
}
