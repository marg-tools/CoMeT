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
#include <cstdlib>
#include <signal.h>


static void HandleSigill(int);
extern "C" void LoadYmm0(const unsigned char *);

int main()
{
    // Create a SIGILL handler in case this processor does not support
    // AVX instructions.
    //
    struct sigaction act;
    act.sa_handler = HandleSigill;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGILL, &act, 0);

    unsigned char ymmVal[32];
    for (unsigned i = 0;  i < sizeof(ymmVal);  i++)
        ymmVal[i] = static_cast<unsigned char>(i+1);

    // If the processor supports AVX, the debugger stops at a breakpoint
    // immediately after loading YMM0.  Otherwise, the debugger stops at
    // a breakpoint in HandleSigill().
    //
    LoadYmm0(ymmVal);

    return 0;
}


static void HandleSigill(int sig)
{
    std::cout << "Processor does not support AVX" << std::endl;
    std::exit(0);
}
