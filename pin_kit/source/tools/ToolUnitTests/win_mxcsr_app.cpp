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
 *  compile this application without any optimizations (/Od)
 */
#include <Windows.h>
#include <iostream>
#include <math.h>
#include <emmintrin.h>

using std::cout;
using std::hex;
using std::endl;

DWORD WINAPI GetMxcsr(VOID * pParams)
{
    unsigned int i = _mm_getcsr();
    cout << hex << i << endl;
    return 0;
}

int main()
{
    GetMxcsr(0);
    HANDLE threadHandle = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GetMxcsr,0,0,0);
    WaitForSingleObject(threadHandle, INFINITE);
    CloseHandle(threadHandle);
    return 0;
}
