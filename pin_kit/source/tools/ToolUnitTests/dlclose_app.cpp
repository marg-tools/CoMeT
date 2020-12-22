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
#include <unistd.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <stdio.h>

#ifdef TARGET_MAC
#define LIBCLOSE "libclose1.dylib"
#else
#define LIBCLOSE "libclose1.so"
#endif

void Load(const char * name)
{
    void * handle;
    
    handle = dlopen(name, RTLD_LAZY);
    if (handle == 0)
    {
        fprintf(stderr,"Load of %s failed\n",name);
        exit(1);
    }
    
    dlclose(handle);
}

int main()
{
    Load(LIBCLOSE);

    return 0;
}
