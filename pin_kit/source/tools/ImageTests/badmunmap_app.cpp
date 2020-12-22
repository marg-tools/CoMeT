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

#include <iostream>
#include <stdio.h>
using std::cout;
using std::endl;
using std::flush;
using std::hex;
using std::dec;
#if defined(TARGET_WINDOWS)
#include<windows.h>
#define EXPORT_SYM extern "C" __declspec(dllexport) __declspec(noinline)
#else
#include <sys/mman.h>
#define EXPORT_SYM extern "C"
#endif

const unsigned int arraySize = 1000;
static char theArray[arraySize];

EXPORT_SYM void AppMarker()
{
    cout << "APP: AppMarker executed" << endl << flush;
}

int main()
{
    cout << "APP: Begin test" << endl << flush;
    cout << "APP: calling munmap(" << hex << (void*)theArray << "," << dec << arraySize << ")" << endl << flush;
#if defined(TARGET_WINDOWS)
    if (0 != VirtualFree(theArray, arraySize, MEM_RELEASE))
    {
        cout << "APP: ERROR: munmap of a variable in the BSS (wrongly) succeeded";
        return 1;
    }
#else
    if (0 == munmap(theArray, arraySize))
    {
        cout << "APP: ERROR: munmap of a variable in the BSS (wrongly) succeeded";
        return 1;
    }
#endif
    perror("APP: munmap failed as expected");
    AppMarker();
    cout << "APP: End test" << endl << flush;
    return 0;
}
