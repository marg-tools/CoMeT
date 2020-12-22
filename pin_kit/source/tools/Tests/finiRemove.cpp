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
 *  Check the PIN_RemoveFiniFunctions interface.
 */

#include "pin_tests_util.H"

VOID BadFini(INT32 code, VOID *v)
{
    TEST(false, "PIN_RemoveFiniFunctions failed");
}

int main(INT32 argc, CHAR **argv)
{
    PIN_Init(argc, argv);

    PIN_AddFiniFunction(BadFini, 0);
    PIN_RemoveFiniFunctions();

    // Never returns
    PIN_StartProgram();
    
    return 0;
}
