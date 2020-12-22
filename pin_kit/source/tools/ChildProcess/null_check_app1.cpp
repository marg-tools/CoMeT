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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sched.h>
#include <string>
#include <signal.h>
using std::string;


int main(int argc, char **argv)
{
    printf("parent:%u-%u\n", getppid(), getpid());

    if (argc < 2)
    {
        fprintf(stderr, "Specify child application name: %s <child app name>\n", argv[0]);
        exit(-1);
    }

	string commandLine(argv[1]);
	char pidArg[10];
	sprintf(pidArg, " %d", getpid());
	commandLine += pidArg;
	
    int res = system(commandLine.c_str());
    if (res !=0)
    {
        fprintf(stderr, "command %s failed\n", commandLine.c_str());
        exit(-1);
    }
	
    if (execv(argv[1], NULL) == -1)
    {
	    fprintf(stderr, "%d:%s\n", errno, strerror(errno));
    }
        
    return 0;
}
