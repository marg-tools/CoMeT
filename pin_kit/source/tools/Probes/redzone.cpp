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
#include "tool_macros.h"
using std::cout;
using std::endl;


void InsideCheckRedZone_Replacement()
{
    char buf[0x200];
    int i;

    cout << "In InsideCheckRedZone_Replacement" << endl;
    for (i = 0; i < (int)sizeof(buf); i++) buf[i] = i & 0xff;
}

/* ===================================================================== */
// Called every time a new image is loaded
// Look for routines that we want to probe
VOID ImageLoad(IMG img, VOID *v)
{
    RTN rtn = RTN_FindByName(img, C_MANGLE("InsideCheckRedZone"));
    if (RTN_Valid(rtn))
    {
        RTN_InsertCallProbed(rtn, IPOINT_BEFORE, (AFUNPTR)InsideCheckRedZone_Replacement, IARG_END);
    }
}

/* ===================================================================== */

int main(int argc, CHAR *argv[])
{
    PIN_InitSymbolsAlt(EXPORT_SYMBOLS);

    PIN_Init(argc,argv);

    IMG_AddInstrumentFunction(ImageLoad, 0);

    PIN_StartProgramProbed();

    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
