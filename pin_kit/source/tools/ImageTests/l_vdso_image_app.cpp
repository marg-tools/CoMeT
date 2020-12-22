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
 *  This application should be used with the l_vdso_image tool.
 *  See documentation in the tool for the test details.
 */

#include <iostream>
#include <sys/time.h>
#include <unistd.h>
using std::cout;
using std::endl;


struct timeval startTime, endTime;

int main( int argc, char *argv[] )
{
    gettimeofday(&startTime, NULL);
    sleep(1);
    gettimeofday(&endTime, NULL);

    long time_spent = ((endTime.tv_sec * 1000000 + endTime.tv_usec) - (startTime.tv_sec * 1000000 + startTime.tv_usec));
    cout << time_spent << endl;

    // Done.
    cout << "APP: Application completed successfully." << endl;
    return 0;
}
