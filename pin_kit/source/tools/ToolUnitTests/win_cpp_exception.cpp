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
#define EXPORT_SYM __declspec( dllexport ) 

int dummy;
/* These Pin* functions are hooks that will be hooked by functions in the 
   exception_monitor.dll tool, in order to verify that PIN has not lost control
   when excecption handling occurs
*/
extern "C"
EXPORT_SYM void PinVerifyInTry ()
{
    dummy=1;
}

extern "C"
EXPORT_SYM
void PinVerifyInCatch ()
{
    dummy=2;
}

extern "C"
EXPORT_SYM
void PinVerifyAfterCatch ()
{
    dummy=3;
}

extern "C"
EXPORT_SYM
void PinVerifyInDestructor ()
{
    dummy=4;
}


// cpp exceptions - Exercise windows exception mechanism 
class MyClass
{
public:
    ~MyClass() 
    { 
        PinVerifyInDestructor ();
        fprintf(stderr, "In MyClass destructor\n"); 
    }
};

void second()
{
    MyClass d;
    fprintf(stderr,"In second\n");
    throw 0x1;
}

int CppException()
{
    int h = 0x1234;
    fprintf(stderr, "In first\n");
    try {
        PinVerifyInTry ();
        second();
    }

    catch(...){
        fprintf(stderr, "In catch\n");
        PinVerifyInCatch ();
    }

    PinVerifyAfterCatch ();
    fprintf(stderr, "In first After catch, h = %x \n" , h); 
    return 0;
}



int main()
{
    CppException();
    return 0;
}