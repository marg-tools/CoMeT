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

/*! @file
 * In addition to what this test checks, we also check these:
 * - In case 'ParentEnv' environment variable was set by the application (after Pin tool over)
 *   which executed the current application we print it here so we can check it from the makefile (by using GREP)
 */

//Child process application
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <string>
#include <iostream>
using std::endl;
using std::string;
using std::cout;


int main(int argc, char * argv[], char * envp[])
{

    int i = 0;

    // In case 'ParentEnv' environment variable was set by the application (after Pin tool over)
    // which executed the current application we print it here so we can check it from the makefile (by using GREP)
    while (envp[i] != 0)
    {
        if (string(envp[i]).compare(string("ParentEnv=1")) == 0)
        {
            cout << envp[i] << endl;
        }
        i++;
    }

    if (argc != 3)
    {
        cout << "Child report: expected 2 parameters, received " << argc-1 << endl;
        return -1;
    }
    if (strcmp(argv[1], "param1 param2") || strcmp(argv[2], "param3"))
    {
        cout << "Child report: wrong parameters: " << argv[1] << " " << argv[2] << endl;
        return -1;
    }
    cout << "Child report: The process works correctly!" << endl;
    return 0;
}
