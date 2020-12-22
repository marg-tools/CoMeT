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
using std::string;

KNOB<string> KnobOutput(KNOB_MODE_WRITEONCE, "pintool", "o", "apc_monitor.out", "output file");

FILE * out;
int numApc = 0;

VOID Fini(INT32 code, VOID *v)
{
    fprintf(out, "Number of APCs = %d \n" ,numApc);
    fclose(out);
}

static void OnApc(THREADID threadIndex, 
                  CONTEXT_CHANGE_REASON reason, 
                  const CONTEXT *ctxtFrom,
                  CONTEXT *ctxtTo,
                  INT32 info, 
                  VOID *v)
{
    if (reason == CONTEXT_CHANGE_REASON_APC)
    {
        ++numApc;
    }
}

int main(INT32 argc, CHAR **argv)
{
    PIN_InitSymbols();
    PIN_Init(argc, argv);

    out = fopen(KnobOutput.Value().c_str(), "w");

    PIN_AddContextChangeFunction(OnApc, 0);

    PIN_AddFiniFunction(Fini, 0);

    // Never returns
    PIN_StartProgram();

    return 0;
}
