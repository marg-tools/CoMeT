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

#include <iostream>

#include "pin.H"
#include "instlib.H"

KNOB<BOOL> KnobReps(KNOB_MODE_WRITEONCE, "pintool", "reps", "0", 
                    "add count with REP prefixed instructions counted only once");

INSTLIB::ICOUNT icount;

// This function is called when the application exits
VOID Fini(INT32 code, VOID *v)
{
    std::cerr << "Count " << icount.Count() << endl;
    if (KnobReps)
        std::cerr << "Count (single REPs) " << icount.CountWithoutRep() << endl;
}

// argc, argv are the entire command line, including pin -t <toolname> -- ...
int main(int argc, char * argv[])
{
    // Initialize pin
    if (PIN_Init(argc, argv))
    {
        PIN_ERROR("Count executed instructions.\n"
                  + KNOB_BASE::StringKnobSummary() + "\n");
    }

    // Activate instruction counter
    if (KnobReps)
        icount.Activate(INSTLIB::ICOUNT::ModeBoth);
    else
        icount.Activate(INSTLIB::ICOUNT::ModeNormal);
        
    // Register Fini to be called when the application exits
    PIN_AddFiniFunction(Fini, 0);
    
    // Start the program, never returns
    PIN_StartProgram();
    
    return 0;
}


