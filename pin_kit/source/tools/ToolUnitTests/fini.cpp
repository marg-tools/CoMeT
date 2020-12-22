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

void Fini(INT32 code, VOID *v)
{
    FILE * f = fopen("fini.out","w");
    fprintf(f,"Fini\n");
    fclose(f);
}

int main(INT32 argc, CHAR **argv)
{
    PIN_Init(argc, argv);
    
    PIN_AddFiniFunction(Fini, 0);

    // Never returns
    PIN_StartProgram();
    return 0;
}
