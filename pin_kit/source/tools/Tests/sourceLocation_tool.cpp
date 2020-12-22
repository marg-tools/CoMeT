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

/*
 * This tool checks a bug in the debug_elf cache mechanism encountered when invoking
 * the PIN_GetSourceLocation API.
 * See sourceLocation_app.cpp for detailed explanations.
 */

#include "pin.H"

VOID onImageUnload(IMG img, VOID *data)
{
    PIN_GetSourceLocation(IMG_LowAddress(img), NULL, NULL, NULL);
}

int main(int argc, char** argv)
{
    PIN_InitSymbols();

    if (!PIN_Init(argc, argv)) {

        IMG_AddUnloadFunction(onImageUnload,  0);

        PIN_StartProgram();

    }
    return(1);
}
