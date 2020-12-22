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
#include <unistd.h>
#include <dlfcn.h>

void Open(char* filename)
{
    void* dlh = dlopen(filename, RTLD_LAZY);
    if( !dlh )
    {
        fprintf(stderr, " Failed to load: %s because: %s", filename, dlerror());
        exit(2);
    }
    dlclose(dlh);
}

int main(int argc, char** argv)
{
    if(argc<1)
    {
        fprintf(stderr, "No image name to load has been supplied" );
        fflush(stderr);
        return 1;
    }

    Open(argv[1]);
    return 0;
}
