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
 *  Make sure the second SYM has greater index than the first one,
 *  and the SYM before the first one is invalid.
 */

#include "pin_tests_util.H"

BOOL test = true;

VOID ImgFirst(IMG img, VOID * v)
{
    if (!test)
        return;
    test = false;

    SYM sym = IMG_RegsymHead(img);
    TEST(SYM_Valid(sym), "IMG_RegsymHead failed");
    UINT32 headIndex = SYM_Index(sym);

    sym = SYM_Next(sym);
    TEST(SYM_Valid(sym) && SYM_Index(sym) > headIndex, "SYM_Index failed");

    sym = SYM_Prev(IMG_RegsymHead(img));
    TEST(sym == SYM_Invalid(), "SYM_Prev failed");
}

int main(INT32 argc, CHAR **argv)
{
    PIN_InitSymbols();
    PIN_Init(argc, argv);
    
    IMG_AddInstrumentFunction(ImgFirst, 0);
    
    // Never returns
    PIN_StartProgram();
    
    return 0;
}
