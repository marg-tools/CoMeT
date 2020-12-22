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

#include <errno.h>
#include <spawn.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

extern char **environ;

using std::string;
using std::cout;
using std::endl;
using std::cerr;

//Wait for a process completion
//Verify it returned the expected exit code

int main(int argc, char * argv[])
{
    posix_spawnattr_t attr;
    posix_spawn_file_actions_t file_actions;
    pid_t pid;
    int pip[2];
    const char* appArgv[] = {
            argv[1],
            "/dev/stdin",
            "/dev/stdout",
            NULL
    };
    if (0 != pipe(pip))
    {
        cout << "pipe failed: " << errno << endl;
        return 1;
    }

    posix_spawn_file_actions_init(&file_actions);
    posix_spawn_file_actions_addclose(&file_actions, 0);
    posix_spawn_file_actions_addclose(&file_actions, pip[1]);
    posix_spawn_file_actions_adddup2(&file_actions, pip[0], 0);
    posix_spawnattr_init(&attr);
    int err = posix_spawn(&pid, argv[1], &file_actions, &attr, (char* const*)appArgv, environ);
    if (err != 0)
    {
        // child process
        cout << "posix_spawn failed with errno " << err << endl;
    }
    else
    {
        int status;
        close(pip[0]);
        write(pip[1], "OK\n", 3);
        close(pip[1]);
        waitpid(pid, &status, 0);
        if (status !=0)
            cout << "Parent report: Child process failed. Status of the child process is "<< WEXITSTATUS(status) << endl;
        else
            cout << "Parent report: Child process exited successfully" << endl;
    }

    posix_spawnattr_destroy(&attr);
    posix_spawn_file_actions_destroy(&file_actions);
    return 0;
}
