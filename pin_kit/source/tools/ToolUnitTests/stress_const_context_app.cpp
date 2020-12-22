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

#include <stdio.h>
#if defined (TARGET_WINDOWS)
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT 
#endif

unsigned int numCallsToStressTestConstContextAppFunc = 0;
int globVal0;
int globVal1;
int globVal2;
int globVal3;
int globVal4;
int globVal5;
extern "C"
DLLEXPORT
void StressTestConstContextAppFunc (int arg0, int arg1, int arg2, int arg3, int arg4, int arg5)
{
    numCallsToStressTestConstContextAppFunc++;
    if ((numCallsToStressTestConstContextAppFunc % 100000)==0)
    {
        printf ("%d calls to StressTestConstContextAppFunc\n", numCallsToStressTestConstContextAppFunc);
        fflush(stdout);
    }
    globVal0 = arg0;
    globVal1 = arg1;
    globVal2 = arg2;
    globVal3 = arg3;
    globVal4 = arg4;
    globVal5 = arg5;
}

int main ()
{
    for (int i=0; i<5000000; i++)
    {
        StressTestConstContextAppFunc (i, i+1, i+2, i+3, i+4, i+5);
    }
}
