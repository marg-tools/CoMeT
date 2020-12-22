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
#include <signal.h>

static void Handle(int);


int main()
{
    struct sigaction act;
    act.sa_handler = Handle;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    if (sigaction(SIGUSR1, &act, 0) != 0)
    {
        std::cerr << "Unable to establish handler\n";
        return 1;
    }

    raise(SIGUSR1);
    return 0;
}

static void Handle(int sig)
{
}
