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
 *   the application which will be executed by the current application.
 *   Application is executed from parent (unlike parent_process.cpp)
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

int main(int argc, char **argv)
{
    printf("parent:%u-%u\n", getppid(), getpid());

    if (argc < 2)
    {
        fprintf(stderr, "Specify child application name: %s <child app name>\n", argv[0]);
        exit(-1);
    }

    // Test injector correctness in macOS*
    signal(SIGUSR1, SIG_IGN);
    signal(SIGUSR2, SIG_IGN);

    // Checking if an environment variable which is set after Pin took over the application is being passed to
    // the application we're about to execute below (as expected)
    setenv("ParentEnv", "1", 1);

    if (execv(argv[1], NULL) == -1)
    {
	    fprintf(stderr, "%d:%s\n", errno, strerror(errno));
    }

    return 0;
}
