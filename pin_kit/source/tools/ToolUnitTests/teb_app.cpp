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

#include <windows.h> 
#include <stdio.h> 

//=======================================================================
// This is the application for testing the teb.dll tool.
// It sets and gets last system error in Windows TEB. The value should
// not change between set and get, even if the tool changes it in an
// analysis routine.
//=======================================================================

int main(int argc, char** argv)
{
    SetLastError(777);
    DWORD lastError = GetLastError();

   if (lastError == 777)
    {
        printf( "Success\n" ); fflush( stdout );
    }
    else
    {
        printf( "Failure\n" ); fflush( stdout );
    }
    return 0;
}
