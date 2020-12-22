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

char * data[100];
INT32 sizeindex[100];

INT32 sizes[] = 
{
    100, 4000, 30, 20, 6000, 24000, 0
};
               
VOID mal(INT32 id)
{
    char * d = data[id];
    INT32 size = sizes[sizeindex[id]];

    if (d)
    {
        for (INT32 i = 0; i < size; i++)
        {
            if (d[i] != id)
            {
                fprintf(stderr,"Bad data id %d data %d\n", id, d[i]);
                exit(1);
            }
        }
        free(d);
    }

    sizeindex[id]++;

    if (sizes[sizeindex[id]] == 0)
        sizeindex[id] = 0;
    size = sizes[sizeindex[id]];

    ASSERTX(size != 0);
    
    
    data[id] = (char*)malloc(size);
    d = data[id];
    for (INT32 i = 0; i < size; i++)
    {
        d[i] = id;
    }
}

VOID Tr(TRACE trace, VOID *)
{
    TRACE_InsertCall(trace, IPOINT_BEFORE, AFUNPTR(mal), IARG_THREAD_ID, IARG_END);
}

int main(INT32 argc, CHAR **argv)
{
    PIN_Init(argc, argv);
    
    TRACE_AddInstrumentFunction(Tr, 0);
    
    // Never returns
    PIN_StartProgram();
    
    return 0;
}
