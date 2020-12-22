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
 *  An example of an application that raises and handles exceptions in SMC 
 *  regions. 
 */
#include "smc_util.h"
#include "../Utils/sys_memory.h"

/*!
 * The main procedure of the application.
 */
int main(int argc, char *argv[])
{
    void * dynamicBuffer;
    dynamicBuffer = MemAlloc(PI_FUNC::MAX_SIZE, MEM_READ_WRITE_EXEC);
    if (dynamicBuffer == 0) 
    {
        cerr << "MemAlloc failed" << endl;
        return 1;
    }

    // Execute SMC that raises and handles exception
    for (int i = 0; i < 3; ++i)
    {
        FOO_FUNC fooFunc;
        fooFunc.SetExceptionMode(true);
        fooFunc.Copy(dynamicBuffer).ExecuteSafe().AssertStatus();
        cerr << fooFunc.Name() << ": " << fooFunc.ErrorMessage() << endl;

        BAR_FUNC barFunc;
        barFunc.SetExceptionMode(true);
        barFunc.Copy(dynamicBuffer).ExecuteSafe().AssertStatus();
        cerr << barFunc.Name() << ": " << barFunc.ErrorMessage() << endl;
    }

    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
