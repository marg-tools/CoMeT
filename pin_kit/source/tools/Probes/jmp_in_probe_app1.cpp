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

#if defined(TARGET_WINDOWS)
#include "windows.h"
#define EXPORT_CSYM extern "C" __declspec( dllexport )
#else
#define EXPORT_CSYM extern "C"
#endif
#include <stdio.h>


int xxx = 1;
EXPORT_CSYM int probed_func(int x)
{
    if (x == 0)
    {
        xxx += 2;
        return(1);
    }
    else
    {
        return (0);
    }
    printf ("probed_func\n");
}


