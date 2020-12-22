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
 * This test checks the usage of the -selfcontained_tool knob. This knob loads the
 * tool with the RTLD_DEEPBIND flag, making it a self-contained library. The test
 * verifies that the usage does not impact Pin or the application. We override two
 * libc functions, "sched_yield" and "sleep", which are used by the application and
 * Pin. Both functions will cause the process to exit with a non-zero return value.
 * "sched_yield" is implemented in this file, while "sleep" is implemented in
 * deepbind_syscalls.o which is linked to the tool.
 */
 
#include "pin.H"
#include <cstdio>
#include <cstdlib>

extern "C" int sched_yield() {
    fprintf(stderr, "ERROR: In deepbind.cpp implementation of sched_yield\n");
    exit(2);
}

int main(int argc, char** argv)
{
    PIN_InitSymbols();
    
    if (!PIN_Init(argc, argv))
    {
        PIN_StartProgram();
    }

    return(1);
}
