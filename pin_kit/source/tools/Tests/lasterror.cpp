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

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

//=======================================================================
// Application which sets and gets last system error in Windows TEB. 
// The value should not be changed between set and get
//=======================================================================

int main()
{
    int errorCode = 0x12345;
    SetLastError(errorCode);
    if(GetLastError() != errorCode)
    {
        fprintf(stderr, "Failure: Bad value returned from GetLastError\n");
        fflush(stderr);
        exit(1);
    } 
           
    return 0;
}

