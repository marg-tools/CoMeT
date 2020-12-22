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

// call OutputDebugString - Exercise windows debug service mechanism 
int DebugService()
{
    int i = 0;
    for(int j = 0 ; j < 100 ; j++)
    {
        OutputDebugString("This is going to the debugger\n");
    }
    fprintf(stderr, "After OutputDebugString, i = %d\n", i);
    return 0;
}


/*------------------------  dispatcher ----------------------*/

int main()
{  
    DebugService();
    return 0;
}