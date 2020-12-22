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
#include <dlfcn.h>

enum ExitType {
    RES_SUCCESS = 0,      // 0
    RES_LOAD_FAILED,      // 1
    RES_RES_INVALID_ARGS  // 2
};

/*
    Expected argv arguments:
    [1] image to load
*/
int main(int argc, char** argv)
{
    if(argc!=2)
    {
        fprintf(stderr, "No enough arguments\n" );
        fflush(stderr);
        return RES_RES_INVALID_ARGS;
    }

    void* handle;

    handle = dlopen(argv[1], RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, " Failed to load: %s because: %s\n", argv[1], dlerror());
        fflush(stderr);
        return RES_LOAD_FAILED;
    }

    return RES_SUCCESS;
}
