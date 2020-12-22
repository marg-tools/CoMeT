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
#include <tool_macros.h>
using std::ofstream;
using std::string;
using std::endl;


/* ===================================================================== */
/* Commandline Switches */
/* ===================================================================== */

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "tls_check_tool.out", "specify file name");

/* ===================================================================== */

ofstream TraceFile;


unsigned long *updateWhenReadyPtr = 0;

VOID DetachPinFromMTApplication(unsigned long *updateWhenReady)
{
    updateWhenReadyPtr = updateWhenReady;
    TraceFile << "Sending detach request" << endl;
    if (PIN_IsProbeMode())
    {
        PIN_DetachProbed();
    }
    else
    {
        PIN_Detach();
    }
}

VOID DetachCompleted(VOID *v)
{
    TraceFile << "Detach completed" << endl;
    *updateWhenReadyPtr = 1;
}

int PinAttached()
{
    TraceFile << "Pin Attached" << endl;
    return 1;
}

VOID ImageLoad(IMG img, void *v)
{
	RTN rtn = RTN_FindByName(img, C_MANGLE("TellPinToDetach"));
	if (RTN_Valid(rtn))
	{
	    TraceFile << "Replacing TellPinToDetach" << endl;
	    if (PIN_IsProbeMode())
        {
            ASSERTX(RTN_IsSafeForProbedReplacement(rtn));
            RTN_ReplaceProbed(rtn, AFUNPTR(DetachPinFromMTApplication));
        }
	    else
	    {
	        RTN_Replace(rtn, AFUNPTR(DetachPinFromMTApplication));
	    }
	}
	
    rtn = RTN_FindByName(img, C_MANGLE("PinAttached"));
    if (RTN_Valid(rtn))
    {
        TraceFile << "Replacing PinAttached" << endl;
        if (PIN_IsProbeMode())
        {
            ASSERTX(RTN_IsSafeForProbedReplacement(rtn));
            RTN_ReplaceProbed(rtn, AFUNPTR(PinAttached));
        }
        else
        {
            RTN_Replace(rtn, AFUNPTR(PinAttached));
        }
    }

}	
/* ===================================================================== */

int main(int argc, CHAR *argv[])
{
    PIN_InitSymbols();

    PIN_Init(argc,argv);

    TraceFile.open(KnobOutputFile.Value().c_str());

    IMG_AddInstrumentFunction(ImageLoad, 0);
    if (PIN_IsProbeMode())
    {
        TraceFile << "Running app in Probe mode" << endl;
        PIN_AddDetachFunctionProbed(DetachCompleted, 0);
        PIN_StartProgramProbed();
    }
    else
    {
        PIN_AddDetachFunction(DetachCompleted, 0);
        TraceFile << "Running app in Jit mode" << endl;
        PIN_StartProgram();
    }

    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
