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

#include <unistd.h>
#include <assert.h>

/* Description:
 * This test checks that Pin does not crash when it runs with an illegal envp array.
 * The expected format of the envp array is an array of strings, each of the form
 * "KEY=VALUE", and the array should be terminated with a NULL pointer.
 * We expect Pin to ignore any illegal entries (i.e. not of the above mentioned form)
 * and to let the application handle these errors by itself. This test checks two
 * forms of illegal entries: one that holds only a KEY and an entry which holds an
 * empty string. We expect Pin to ignore the illegal entries and the test application
 * to run properly despite the illegal environment.
 */

/* Usage:
 * We assume that a copying test application is passed along with "from" and "to"
 * parameters. We will then use execve to run the test application with an illegal
 * environment to see if Pin crashes or ignores the environment.
 */
int main(int argc, char* argv[], char* envp[])
{
    int res;
    char* badEnvp[] = { "KEY", "", NULL };
    
    /* Make sure that we got at least the 3 arguments mentioned in the usage note.*/
    assert(argc >= 4);

    return execve(argv[1], &argv[1], badEnvp);
}
