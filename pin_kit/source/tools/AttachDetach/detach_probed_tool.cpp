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
 */

#include "pin.H"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <assert.h>
#include "tool_macros.h"


/* ===================================================================== */
/* Commandline Switches */
/* ===================================================================== */


unsigned long *updateWhenReadyPtr = 0;

VOID DetachPinFromMTApplication(unsigned long *updateWhenReady)
{
    updateWhenReadyPtr = updateWhenReady;
	fprintf(stderr, "Pin tool: sending detach request\n");
	PIN_DetachProbed();
}

VOID DetachCompleted(VOID *v)
{
	fprintf(stderr, "Pin tool: detach is completed\n");
    *updateWhenReadyPtr = 1;
}


VOID ImageLoad(IMG img, void *v)
{
	RTN rtn = RTN_FindByName(img, C_MANGLE("TellPinToDetach"));
    if (RTN_Valid(rtn))
	{
		RTN_ReplaceProbed(rtn, AFUNPTR(DetachPinFromMTApplication));
	}
	
}	
/* ===================================================================== */

int main(int argc, CHAR *argv[])
{
    PIN_InitSymbols();

    PIN_Init(argc,argv);

    IMG_AddInstrumentFunction(ImageLoad, 0);
    PIN_AddDetachFunctionProbed(DetachCompleted, 0);
    PIN_StartProgramProbed();
    
    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
