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

/*
  This DLL causes exception in destructor of global object.
  It should happen after application that loaded this DLL started process exit flow.
*/
#include <stdio.h>
#include <Windows.h>

int * nullPtr = 0;

// Define global object with destructor that throws hardware exception.
class MyClass
{
public:
    ~MyClass()
    {
        __try
        {
            // Causes exception.
            *nullPtr = 5;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            printf("Caught exception %X\n", GetExceptionCode());
        }
    }
} myObj;

extern "C" __declspec(dllexport) int Something() { return 0; }
