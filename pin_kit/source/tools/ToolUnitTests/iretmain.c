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
 * Call the iret assembler stubs.
 */

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#define __USE_GNU
#include <ucontext.h>

typedef unsigned int  UINT32;

extern int iretTest();

# define registerSegvHandler() ((void)0)

int main (int argc, char ** argv)
{
    int result;
    int ok = 0;
    int tests = 0;

    registerSegvHandler();

    tests++;
    fprintf(stderr, "Calling iret\n");
    result = iretTest();
    fprintf(stderr, "iretd result = %d %s\n", result, result == -1 ? "OK" : "***ERROR***");

    ok += (result == -1);

    return (ok == tests) ? 0 : -1;
}
