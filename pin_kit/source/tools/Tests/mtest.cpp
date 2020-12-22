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
PIN_LOCK pinLock;

VOID ThreadStart(THREADID threadid, CONTEXT *ctxt, INT32 flags, VOID *v)
{
    PIN_GetLock(&pinLock, threadid+1);
    fprintf(out, "thread begin %d flags %x\n",threadid, flags);
    PIN_ReleaseLock(&pinLock);
}
    
VOID ThreadFini(THREADID threadid, const CONTEXT *ctxt, INT32 code, VOID *v)
{
    PIN_GetLock(&pinLock, threadid+1);
    fprintf(out, "thread end %d code %d\n",threadid, code);
    PIN_ReleaseLock(&pinLock);
}
    
VOID TraceBegin(VOID * ip, THREADID threadid)
{
    PIN_GetLock(&pinLock, threadid+1);
    fprintf(out, "%p: %d\n", ip, threadid);
    PIN_ReleaseLock(&pinLock);
}

VOID Fini(INT32 code, VOID *v)
{
    fprintf(out, "Fini: code %d\n", code);
}

VOID Trace(TRACE trace, VOID *v)
{
    TRACE_InsertCall(trace, IPOINT_BEFORE, AFUNPTR(TraceBegin), IARG_INST_PTR, IARG_THREAD_ID, IARG_END);
}

int main(INT32 argc, CHAR **argv)
{
    PIN_InitLock(&pinLock);
    
    out = fopen("mt.out", "w");
    
    PIN_Init(argc, argv);
    
    TRACE_AddInstrumentFunction(Trace, 0);
    PIN_AddThreadStartFunction(ThreadStart, 0);
    PIN_AddThreadFiniFunction(ThreadFini, 0);
    PIN_AddFiniFunction(Fini, 0);
    
    // Never returns
    PIN_StartProgram();
    
    return 0;
}
