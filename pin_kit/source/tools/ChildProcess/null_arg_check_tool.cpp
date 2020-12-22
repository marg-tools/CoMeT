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

#include "pin.H"
#include <iostream>
#include "arglist.h"
#include <stdio.h>

/* ===================================================================== */
/* Command line Switches */
/* ===================================================================== */


BOOL FollowChild(CHILD_PROCESS childProcess, VOID * userData)
{
    return TRUE;
}        

/* ===================================================================== */
VOID ImageLoad(IMG img, VOID *v)
{
    BOOL jitMode = (v==0);
    if (IMG_IsMainExecutable(img))
    {
        fprintf(stdout, "Image %s is loaded in %s mode\n", IMG_Name(img).c_str(), (jitMode?"JIT":"PROBE"));
    }
}

int main(INT32 argc, CHAR **argv)
{
    PIN_InitSymbols();

    PIN_Init(argc, argv);

    PIN_AddFollowChildProcessFunction(FollowChild, 0);

    // Never returns
    if (PIN_IsProbeMode())
    {
        IMG_AddInstrumentFunction(ImageLoad, (VOID *)1);
        PIN_StartProgramProbed();
    }
    else
    {
        IMG_AddInstrumentFunction(ImageLoad, 0);
        PIN_StartProgram();
    }
    return 0;
}

