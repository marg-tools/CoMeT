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

#define _GNU_SOURCE
#include <dlfcn.h>
#include <link.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Macro to create empty function which won't be opt-out by
// the compiler
#define EMPTY_FUNCTION(name) \
    void name();        \
    __asm__(              \
    ".global " #name "\n" \
    #name ":\n"          \
    "ret\n"               \
    )

EMPTY_FUNCTION(AfterLoadLibrary);
EMPTY_FUNCTION(AfterUnloadLibrary);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <path to dynamic library>\n", argv[0]);
        exit(1);
    }
    const char* file = argv[1];
    printf("Loading shared object %s\n", file);
    fflush(stdout);
    void *handle = dlopen(file, RTLD_NOW | RTLD_LOCAL);
    if (NULL == handle)
    {
        fprintf(stderr,"Failed to load %s - %s\n", file, dlerror());
        exit(1);
    }
    AfterLoadLibrary();
    printf("Unloading shared object %s\n", file);
    fflush(stdout);
    dlclose(handle);
    AfterUnloadLibrary();

    return 0;
}
