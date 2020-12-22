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
#include <stdlib.h>
#include <windows.h>
#include <iostream>

using std::cerr;
using std::endl;

extern "C" __declspec(noinline, dllexport) int PinIsAttached()
{
    return 0;
}

extern "C" __declspec(noinline, dllexport) int PinIsDetached()
{
    return 1;
}

extern "C" __declspec(noinline, dllexport) void FirstProbeInvoked()
{
    cerr << "FirstProbeInvoked shouldn't be called" << endl;
    abort();
}

extern "C" __declspec(noinline, dllexport) void SecondProbeInvoked()
{
    cerr << "SecondProbeInvoked shouldn't be called" << endl;
    abort();
}

int main()
{
    while (!PinIsAttached()) SwitchToThread();
    FirstProbeInvoked();
    while (!PinIsDetached()) SwitchToThread();
    while (!PinIsAttached()) SwitchToThread();
    SecondProbeInvoked();
    while (!PinIsDetached()) SwitchToThread();
    while (!PinIsAttached()) SwitchToThread();

    cerr << "Test passed!" << endl;

    return 0;
}
