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
#include <dlfcn.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

#define EXPORT_SYM extern "C"

EXPORT_SYM bool AfterAttach2();

enum ExitType {
    RES_SUCCESS = 0,      // 0
    RES_LOAD_FAILED,      // 1
};

bool AfterAttach2()
{
    // Pin sets an anslysis function here to notify the application when Pin attaches to it.
    return false;
}

int main (int argc, char *argv[])
{
    void *handle = dlopen(argv[1], RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, " Failed to load: %s because: %s\n", argv[1], dlerror());
        fflush(stderr);
        exit(RES_LOAD_FAILED);
    }

    while(!AfterAttach2())
    {
        sleep(1);
    }

    handle = dlopen(argv[2], RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, " Failed to load: %s because: %s\n", argv[1], dlerror());
        fflush(stderr);
        exit(RES_LOAD_FAILED);
    }

    while(1)
    {
        // expected to be stopped by tool.
        sleep(1);
    }

    return RES_SUCCESS;
}
