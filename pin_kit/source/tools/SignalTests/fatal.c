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

#include <unistd.h>
#include <signal.h>

int main()
{
    struct sigaction act;

    // Make sure SIGINT isn't ignored.  On some systems, SIGINT is initially
    // ignored when this test is run from scons / make.
    //
    act.sa_handler = SIG_DFL;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGINT, &act, 0);

    kill(getpid(), SIGINT);
    return 0;
}
