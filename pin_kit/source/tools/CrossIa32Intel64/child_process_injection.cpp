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

// This tool is being used by the tests: "child_process_injection.test" and "child_process_injection1.test" .

#include "pin.H"
#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;


/* ===================================================================== */
VOID Fini(INT32 code, VOID *v)
{
    cout << "End of tool" << endl;
}


BOOL FollowChild(CHILD_PROCESS childProcess, VOID * userData)
{
    return TRUE; // run childProcess under Pin instrumentation
}        


/* ===================================================================== */

int main(INT32 argc, CHAR **argv)
{
    PIN_Init(argc, argv);
    
    PIN_AddFollowChildProcessFunction(FollowChild, 0);

    PIN_AddFiniFunction(Fini, 0);
    
    // Never returns
    PIN_StartProgram();

    return 0;
}
