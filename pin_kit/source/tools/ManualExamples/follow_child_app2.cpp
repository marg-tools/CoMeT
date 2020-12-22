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

/*! @file
 * In addition to what this test checks, we also check these:
 * - Checking if an environment variable which is set after Pin took over the application is being passed to
 *   the current application which was executed by the previous application
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <assert.h>
#include <iostream>
using std::string;


int main(int argc, char **argv, char * envp[])
{
    printf("child:%u-%u\n", getppid(), getpid());

    int i = 0;

    // Verifying that 'ParentEnv' environment variable which was set by the application (after Pin tool over)
    // which executed the current application was passed as expected
    bool parentEnvPassed = false;
    while (envp[i] != 0)
    {
        if (string(envp[i]).compare(string("ParentEnv=1")) == 0)
        {
            parentEnvPassed = true;
        }
        i++;
    }

    assert(parentEnvPassed);

    return 0;
}
