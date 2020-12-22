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

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

/***************************************************************************/

static void event_on_process_fork_before(void)
{
    fprintf(stdout, "event_on_process_fork_before\n"); fflush(stdout);
}

static void event_on_process_fork_after_in_parent(void)
{
    fprintf(stdout, "event_on_process_fork_after_in_parent\n"); fflush(stdout);
    FILE* fd = fopen("father.log", "w");
    fprintf(fd, "This is temporary log written from within pthread_atfork hook");
    fclose(fd);
}

static void event_on_process_fork_after_in_child(void)
{
    fprintf(stdout, "event_on_process_fork_after_in_child\n"); fflush(stdout);
    FILE* fd = fopen("child.log", "w");
    fprintf(fd, "This is temporary log written from within pthread_atfork hook");
    fclose(fd);
}

/***************************************************************************/

int testFork()
{
	pthread_atfork(event_on_process_fork_before,
		event_on_process_fork_after_in_parent,
		event_on_process_fork_after_in_child);
	if (fork())
	{
		int res = 0;
		
		fprintf(stdout, "after fork before wait of child\n"); fflush(stdout);
		wait(&res);
	}
	else
	{
		fprintf(stdout, "from child before exit\n"); fflush(stdout);
		exit(0);
	}

	return 0;
}

/***************************************************************************/

int main ( )
{

	fprintf(stdout, "main before fork\n"); fflush(stdout);

	testFork();

	fprintf(stdout, "main after fork\n"); fflush(stdout);

	return 0;
}

