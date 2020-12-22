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

#include <fstream>
#include "pin.H"

KNOB<std::string> KnobOut(KNOB_MODE_WRITEONCE, "pintool", "o",
    "start-fini-callback.out", "Output file");

std::ofstream Out;

THREADID myThread = INVALID_THREADID;

static void OnThreadStart(THREADID tid, CONTEXT *, INT32, VOID *)
{
    if (INVALID_THREADID == myThread)
    {
        myThread = tid;
        Out << "OnThreadStart for thread " << tid << std::endl;
    }
}

static void OnThreadFini(THREADID tid, const CONTEXT *, INT32, VOID *)
{
    if (tid == myThread)
    {
        Out << "OnThreadFini for thread " << tid << std::endl;
    }
}

static void OnExit(INT32, VOID *)
{
    Out << "OnExit" << std::endl;
}


int main(int argc, char * argv[])
{
    PIN_Init(argc, argv);

    Out.open(KnobOut.Value().c_str());

    PIN_AddThreadStartFunction(OnThreadStart, NULL);
    PIN_AddThreadFiniFunction(OnThreadFini, NULL);
    PIN_AddFiniFunction(OnExit, NULL);
    PIN_StartProgram();
    return 1;
}
