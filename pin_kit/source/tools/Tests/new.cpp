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
#include "pin.H"

KNOB<INT32> KnobMaxSize(KNOB_MODE_WRITEONCE, "pintool",
    "m", "0x100000", "Total bytes to allocate");
KNOB<INT32> KnobIncrement(KNOB_MODE_WRITEONCE, "pintool",
    "i", "100", "Bytes to new() each time");


VOID MalNew()
{
    for (INT32 size = 0; size < KnobMaxSize; size+=KnobIncrement)
    {
        CHAR * m = new CHAR[KnobIncrement];
        
        if (m == 0)
        {
            fprintf(stderr, "Failed new\n");
        }
    }
}

int main(INT32 argc, CHAR **argv)
{
    PIN_Init(argc, argv);

    MalNew();
    
    // Never returns
    PIN_StartProgram();
    
    return 0;
}
