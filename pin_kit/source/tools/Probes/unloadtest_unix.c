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
#include "tool_macros.h"

void Load(char * name, int expect)
{
    int val;
    
    void * handle;
    int (*sym)();
    
    handle = dlopen(name, RTLD_LAZY);
    if (handle == 0)
    {
        fprintf(stderr,"Load of %s failed\n",name);
        exit(1);
    }
    
    sym = (int(*)())dlsym(handle, "one");
    fprintf(stderr, "Address of sym is %p\n",sym);
    
    if (sym == 0)
    {
        fprintf(stderr,"Dlsym of %s failed\n",name);
        exit(1);
    }
    
    val = sym();
    if (val != expect)
        exit(1);
    
    dlclose(handle);
}

int main()
{
    Load(SHARED_LIB("libone"), 1);
    Load(SHARED_LIB("libtwo"), 2);

    return 0;
}

