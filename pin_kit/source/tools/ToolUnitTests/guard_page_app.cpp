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
 * This test application verifies that Pin on Windows correctly updates the 
 * TEB.NtTib.StackLimit value when the application and/or tool touches the 
 * guard page of the application stack.
 * This application must be run with the "guard_page" test tool.
 */

#include <string>
#include <iostream>
#include <windows.h>

using std::endl;
using std::string;
using std::cerr;

/*!
 * Return page size in bytes.
 */
static size_t PageSize = 0;
size_t GetPageSize()
{
    if (PageSize == 0)
    {
        SYSTEM_INFO sysInfo;
        GetSystemInfo(&sysInfo);
        PageSize = static_cast<size_t>(sysInfo.dwPageSize);
    }
    return PageSize;
}

/*!
* Return pointer to the Thread Information Block of the current thread
*/
NT_TIB * GetCurrentTib()
{
    return (NT_TIB *)NtCurrentTeb();
}

/*!
 * Get starting address of the guard page in the stack of the current thread 
 */
char * GetStackGuardPage()
{
    return ((char *)(GetCurrentTib()->StackLimit)) - GetPageSize();
}

//==========================================================================
// Printing utilities
//==========================================================================
string UnitTestName("guard_page");

static void Abort(const string & msg)
{
    cerr << UnitTestName << " Failure: " << msg << endl;
    exit(1);
}


/*!
 * The main procedure of the application.
 */
int main(int argc, char *argv[])
{
    char dummy;

    for (int i = 0; i < 5; i++)
    {
        char *  guardPage = GetStackGuardPage();
        dummy = *guardPage;  // touch (read) the guard page
        if (GetStackGuardPage() != (guardPage - GetPageSize()))
        {
            Abort("Stack limit is not updated");
        }
    }
    cerr << UnitTestName << " : Completed successfully" << endl;
    return 0;
}
