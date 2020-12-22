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
 *  This test checks pin environment on Linux
 */
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "pin.H"


void VerifyEnvVarNotSet(const char* varName)
{
    char *envVar = getenv(varName);
    if (NULL != envVar)
    {
        printf("check_env_tool ERROR: %s should not be a part of Pin environment.\n", varName);
        printf("%s = %s\n", varName, envVar);
        exit(1);
    }
}


int main(int argc, char * argv[])
{

    PIN_Init(argc, argv);

    VerifyEnvVarNotSet("LD_ASSUME_KERNEL");
    VerifyEnvVarNotSet("LD_PRELOAD");
    VerifyEnvVarNotSet("LD_BIND_NOW");

    // Never returns
    PIN_StartProgram();

    return 2;
}
