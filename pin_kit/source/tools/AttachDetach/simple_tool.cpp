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

/* ===================================================================== */
/* Command line Switches */
/* ===================================================================== */

KNOB<BOOL> KnobToolProbeMode(KNOB_MODE_WRITEONCE, "pintool", "probe", "0", "invoke tool in probe mode");


/* ===================================================================== */

int main(INT32 argc, CHAR **argv)
{
    PIN_Init(argc, argv);

    // Never returns
    if (KnobToolProbeMode)
    {
        PIN_StartProgramProbed();
    }
    else
    {
        PIN_StartProgram();
    }
    return 0;
}
