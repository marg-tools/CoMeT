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
 * This program receives a pid as its argument and sends a SIGTERM to it.
 */

#include <cassert>
#include <cstdlib>
#include <signal.h>
#include <sys/types.h>

// argv[1] is expected to be the pid to kill.
int main(int argc, char** argv) {
    assert(argc == 2);
    int pid = atoi(argv[1]);
    assert(pid > 1);
    kill(pid, SIGTERM);
    return 0;
}
