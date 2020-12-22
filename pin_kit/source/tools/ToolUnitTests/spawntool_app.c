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
 * A trivial application that does nothing, but contains function that loops forever
 * which is invoked by Pin's aplication thread creation routine.
 */

#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

void doNothing()
{
    volatile int loopCount;

    for (;;)
    {
        sched_yield();
        loopCount++;
    }
}

void (*funcPtr)();

int main(int argc, char ** argv)
{
    // Ensure that the compiler thinks there is a reference to doNothing.
    funcPtr = doNothing;
    sleep(10);
    exit(0);
}
