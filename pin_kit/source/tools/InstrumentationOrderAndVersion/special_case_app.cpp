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

/*! @file
 * 
 */
#ifdef TARGET_WINDOWS
#include <windows.h>
#define EXPORT_CSYM extern "C" __declspec( dllexport )
#else
#define EXPORT_CSYM extern "C" 
#endif

int a;

EXPORT_CSYM void watch_rtn(int arg)
{
    a = arg;
}

EXPORT_CSYM int main(int argc, char *argv[])
{
    watch_rtn(10);
    watch_rtn(20);
    watch_rtn(20);
    watch_rtn(-1);
    watch_rtn(10);
    watch_rtn(10);
    watch_rtn(20);
    return 0;
}
