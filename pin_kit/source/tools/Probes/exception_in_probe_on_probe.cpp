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

#include "pin.H"

#ifdef TARGET_WINDOWS
namespace WND
{
#include <windows.h>
}
#endif
#include "tool_macros.h"

typedef int (* foo_t)();

static AFUNPTR foo_ptr1;
static AFUNPTR foo_ptr2;

static int foo_rep1()
{
	printf("foo rep1 called\n");

	return ((foo_t)foo_ptr1)();
}

static int foo_rep2()
{
	printf("foo rep2 called\n");

	return ((foo_t)foo_ptr2)();
}

static VOID on_module_loading(IMG img, VOID *data)
{
    if (IMG_IsMainExecutable(img))
    {
        RTN routine = RTN_FindByName(img, C_MANGLE("foo"));
        if (!RTN_Valid(routine))
        {
            routine = RTN_FindByName(img, C_MANGLE("_foo"));
        }

        if (RTN_Valid(routine))
        {
            foo_ptr1 = RTN_ReplaceProbed(routine, (AFUNPTR)(foo_rep1));
            foo_ptr2 = RTN_ReplaceProbed(routine, (AFUNPTR)(foo_rep2));
        }
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
