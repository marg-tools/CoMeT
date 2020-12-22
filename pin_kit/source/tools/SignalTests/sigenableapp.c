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
 * This is a contrived application that works with the "sigenable" tool.
 */

#include <signal.h>
#include <unistd.h>

extern void NotTraced();
extern void IsTraced();

int main()
{
    /*
     * These function calls should not be traced
     */
    IsTraced();
    NotTraced();

    /*
     * This signal is caught by the tool and enables instrumentation.
     * More commonly, the application wouldn't send the signal, but the
     * user would type "kill -USR2 <pid>" at the command prompt while
     * the application was running under Pin.
     */
    kill(getpid(), SIGUSR2);

    /*
     * This call is traced by Pin.
     */
    IsTraced();
    return 0;
}
