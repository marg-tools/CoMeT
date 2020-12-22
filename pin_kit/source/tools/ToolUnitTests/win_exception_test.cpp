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
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include "windows.h"


static int enteredFilter = 0;
static int MyExceptionFilter(LPEXCEPTION_POINTERS exceptPtr)
{
    enteredFilter = 1;
    return EXCEPTION_EXECUTE_HANDLER;

}

int main( int argc, char * argv[] )
{
__try
    {
        __asm
        {
            xor ebx, ebx
            mov eax, dword ptr [ebx]  // test verifies that Pin does NOT optimize away this instruction
                                      // which would mean the exception is not generated
            xor eax, eax              // makes previous load of eax dead - make sure
				                      // pin does not optimize away that load which would
									  // cause the exception not to occur.
         }
    }
    __except (MyExceptionFilter(GetExceptionInformation()))
    {
    }
	if (!enteredFilter)
    {
        printf( "FAILURE: MyExceptionFilter not entered\n");
		fflush (stdout);
		return (-1);
    }
    return 0;
    
}
