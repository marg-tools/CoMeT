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

#include <string>
#include <iostream>
#include <errno.h>
#include <windows.h>

using std::cout;
using std::endl;

/**************************************************/

extern "C" __declspec( dllexport ) __declspec( noinline ) int AfterSetCurrentDirectory()
{
    // Pin replaces this function to validate loading of a Pin DLL.
    cout << "Should not run" << endl;
    return 3;   // Returns failure 3 if not instrumented.
}

int main()
{
    // Modify current working directory of the process.
    if (!SetCurrentDirectory("..\\")) return 4; // Return on failure.

    char buf[MAX_PATH * 10];
    DWORD nsize = GetCurrentDirectory(sizeof(buf), buf);
    if ((nsize == 0) || (nsize > sizeof(buf))) return 5;    // Can't get current directory name.
    cout << "Current directory: " << buf << endl;

    int res = AfterSetCurrentDirectory();
    return res;
}
