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
#include "pin.H"

// Just test that we can allocate registers and fail when we expect to.

int main(int argc, char **argv)
{
    const int nScratch = REG_INST_TOOL_LAST-REG_INST_TOOL_FIRST+1;
    int seen[nScratch];
    bool failed = false;

    PIN_Init(argc, argv);

    for (int i=0; i<nScratch; i++)
        seen[i] = 0;

    // Claim all the registers we expect to be able to claim
    for (int i=0; i<nScratch; i++)
    {
        REG scratch = PIN_ClaimToolRegister();
        if (scratch < REG_INST_TOOL_FIRST ||
            scratch > REG_INST_TOOL_LAST)
        {
            printf ("Failed: got a non-scratch register (%d)\n", int(scratch));
            failed = true;
        }
        seen[scratch-REG_INST_TOOL_FIRST]++;
    }

    // Check that we fail when we try to allocate an extra one.
    if (PIN_ClaimToolRegister() != REG_INVALID())
    {
        printf ("Failed: got register when we shouldn't have\n");
        failed = true;
    }

    // Check that we got each register once
    for (int i=0; i<nScratch; i++)
    {
        if (seen[i] != 1)
        {
            printf ("Failed: saw REG_INST_G%d %d times\n", i, seen[i]);
            failed = true;
        }
    }

    if (!failed)
        printf ("Passed\n");
    
    // No need to run the code...
    exit(failed ? 1 : 0);
}
