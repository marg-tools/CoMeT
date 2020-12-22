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
 *  This file tests pin tool failure behavior
 */

#include <stdio.h>
#include "pin.H"

/* ===================================================================== */

VOID Trace(TRACE trace, void *v)
{
    char * p = 0;
    char foo = *p; // SEGV
    printf ("%d\n", foo);
}

/* ===================================================================== */

int main(int argc, char *argv[])
{
    PIN_Init(argc, argv);
    
    TRACE_AddInstrumentFunction(Trace, 0);

    // Never returns
    PIN_StartProgram();
    
    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
