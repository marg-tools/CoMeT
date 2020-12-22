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
#include <string.h>
#include <assert.h>
#include <stdlib.h>
// The program sets many environment variable and then runs the application passed by parameters
int main(int argc, char ** argv)
{
    int idx=0;
    char envname[50];
    char **newArg;
    if (argc>1)
        newArg=&argv[1];
    else
    {
        printf("ERROR: mysetenv must get an application to run as a parameter (e.g \"./mysetenv /bin/ls\") \n");
        return 1;
    }

    for(idx=0;idx<1500;idx++)
    {
        sprintf(envname, "ZZZ_%d", idx);
        setenv(envname, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 1);
    }
    
    return execv(newArg[0], newArg);

}
