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
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>


int main()
{

    pid_t child_id = fork();
	if (child_id == 0)
	{
		printf("APPLICATION: After fork in child\n");
	}
	else
	{
		printf("APPLICATION: After fork in parent\n");
	}

    wait(0);
    return 0;
}
