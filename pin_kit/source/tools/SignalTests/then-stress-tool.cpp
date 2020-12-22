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
 * This tool stresses Pin's ability to deliver signals during a "then" analysis routine.
 * It must be run with the "then-stress-app.cpp" application.
 */

#include <iostream>
#include <cstdlib>
#include "pin.H"


static VOID OnRoutine(RTN, VOID *);
static ADDRINT IfTrue();
static VOID ThenFunction();
static VOID OnExit(INT32, VOID *);

static BOOL GotThen = FALSE;


int main(int argc, char * argv[])
{
    PIN_Init(argc, argv);
    PIN_InitSymbols();

    RTN_AddInstrumentFunction(OnRoutine, 0);
    PIN_AddFiniFunction(OnExit, 0);

    PIN_StartProgram();
    return 0;
}

static VOID OnRoutine(RTN rtn, VOID *)
{
#if defined(TARGET_MAC)
    if (RTN_Name(rtn) == "_DoThenInstrumentation")
#else
    if (RTN_Name(rtn) == "DoThenInstrumentation")
#endif
    {
        RTN_Open(rtn);
        INS_InsertIfCall(RTN_InsHead(rtn), IPOINT_BEFORE, AFUNPTR(IfTrue), IARG_END);
        INS_InsertThenCall(RTN_InsHead(rtn), IPOINT_BEFORE, AFUNPTR(ThenFunction), IARG_END);
        RTN_Close(rtn);
    }
}

static ADDRINT IfTrue()
{
    return 1;
}


static VOID ThenFunction()
{
    // A big delay here makes it very likely that a signal will be delivered during this
    // "then" analysis routine.
    //
    GotThen = TRUE;
    for (volatile unsigned long i = 0;  i < 100000;  i++)
        ;
}


static VOID OnExit(INT32, VOID *)
{
    if (!GotThen)
    {
        std::cerr << "Analysis routine not exectued." << std::endl;
        std::exit(1);
    }
}
