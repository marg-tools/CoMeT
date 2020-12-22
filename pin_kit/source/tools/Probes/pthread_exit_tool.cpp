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
#include <string>
#include <stdlib.h>
#include "tool_macros.h"

#include "pin.H"


typedef void (* THREAD_EXIT_T)(void *);

static VOID pthread_exit_rep(THREAD_EXIT_T orig_pte, VOID *p0)
{
    printf("pthread_exit_rep called\n");

    orig_pte(p0);

}

static VOID on_module_loading(IMG img, VOID *data)
{
    RTN routine = RTN_FindByName(img, C_MANGLE("pthread_exit"));

    if (RTN_Valid(routine))
    {
        PROTO pte_proto = PROTO_Allocate( PIN_PARG(int), CALLINGSTD_DEFAULT,
                                          "pthread_exit", PIN_PARG(void *), PIN_PARG_END() );
        AFUNPTR orig_pte = RTN_ReplaceSignatureProbed(routine, (AFUNPTR)pthread_exit_rep,
                IARG_PROTOTYPE, pte_proto,
                IARG_ORIG_FUNCPTR,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                IARG_END);
        ASSERTX(orig_pte != 0);
    }
}

int main(int argc, char** argv)
{
    PIN_InitSymbols();

    if (!PIN_Init(argc, argv))
    {
        IMG_AddInstrumentFunction(on_module_loading,  0);        

        PIN_StartProgramProbed();
    }

    exit(1);
}
