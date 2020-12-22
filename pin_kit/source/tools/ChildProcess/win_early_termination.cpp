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

#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <Dbghelp.h>

using std::flush;
using std::endl;
using std::cout;

extern "C" __declspec(dllimport) int Something();

//this application has static linking with dll which terminate the process in it's DllMain(PROCESS_ATTACH)
int main()
{
    //should never get here
    cout << "should never get here" << endl << flush;
    volatile int i = Something();
    HANDLE token;
    OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &token);
    GetTimestampForLoadedLibrary(GetModuleHandle("advapi32.dll"));

    exit(-1);
    return 0;
}
