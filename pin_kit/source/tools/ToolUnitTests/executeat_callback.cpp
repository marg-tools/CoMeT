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

//
//  Sample usage:
//    pin -mt -t executeat_callback -- thread_wait

#include <stdio.h>
#include <iostream>
#include "pin.H"

PIN_LOCK pinLock;

VOID ThreadStart( THREADID threadid, CONTEXT *ctxt, INT32 flags, VOID *v )
{
    // **** PIN_ExecuteAt() cannot be called from a callback!!!  ****
    // **** This is a test to ensure that an error is reported.  ****
    // **** Do not try this at home.                             ****
    
    PIN_ExecuteAt( ctxt );
}


int main(INT32 argc, CHAR **argv)
{
    PIN_InitLock(&pinLock);

    PIN_InitSymbols();

    PIN_Init(argc, argv);
    
    PIN_AddThreadStartFunction(ThreadStart, 0);
    
    // Never returns
    PIN_StartProgram();
    
    return 0;
}

