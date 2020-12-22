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

FILE * out;


// Inspect the sequence, but do not instrument
VOID Trace(TRACE trace, VOID *v)
{
    fprintf(out, "Trace address %p\n",(CHAR*)(TRACE_Address(trace)));

    for (BBL bbl = TRACE_BblHead(trace); BBL_Valid(bbl); bbl = BBL_Next(bbl))
    {
        for (INS ins = BBL_InsHead(bbl); INS_Valid(ins); ins = INS_Next(ins))
        {
            fprintf(out, "  %p\n",(CHAR*)(INS_Address(ins)));
        }
    }

    fprintf(out, "\n");
}

int main(INT32 argc, CHAR **argv)
{
    out = fopen("sequence.out", "w");
    
    PIN_Init(argc, argv);
    
    TRACE_AddInstrumentFunction(Trace, 0);
    
    // Never returns
    PIN_StartProgram();
    
    return 0;
}
