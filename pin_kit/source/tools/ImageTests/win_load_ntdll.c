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

// Dynamically load ntdll.dll
// Observe side effect (temporal loading of extra ntdll.dll copy) on 64-bit Windows 7 OS family.

int main()
{
    HMODULE hntdll;
    char ntname[MAX_PATH];
    DWORD name_size = GetSystemDirectory(ntname, sizeof(ntname));
    strcat(ntname, "\\ntdll.dll");
    // WOW64 file system redirection is on by default in Windows 64-bit versions since Server 2003.

    // During this call OS may temporary load extra copy of ntdll.dll
    // Nevertheless returned handle refers to existing copy and its reference counter is incremented.
    hntdll = LoadLibrary(ntname);
    if (hntdll != NULL) FreeLibrary(hntdll);
    printf("Success\n");
    return 0;
}
