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

// Application that creates new process

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <string>

//Wait for a process completion
//Verify it returned the expected exit code

using std::string;
using std::endl;
using std::cout;

int main(int argc, char * argv[])
{
    char *childArgvArray[6];
    childArgvArray[0] = argv[1];
    childArgvArray[1] = argv[2];
    childArgvArray[2] = argv[3];
    childArgvArray[3] = argv[4];
    childArgvArray[4] = argv[5];
    childArgvArray[5] = argv[6];

    pid_t pid = fork();
    if (pid == 0)
    {
        // child process
        execv(childArgvArray[0], childArgvArray);
        cout << "Execve failed "<< argv[1] << " " << argv[2] << " " << argv[3] << endl;
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        if (status !=0)
            cout << "Parent report: Child process failed. Status of the child process is "<< WEXITSTATUS(status) << endl;
        else
            cout << "Parent report: Child process exited successfully" << endl;
    }
    return 0;
}
