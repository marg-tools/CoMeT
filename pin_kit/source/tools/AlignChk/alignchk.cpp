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

/// @file alignchk.cpp

#include "pin.H"
#include <iostream>
#include <iomanip>
#include <stdlib.h>

#include "alignchk.H"
using std::cerr;
using std::endl;
void
usage()
{
    cerr << KNOB_BASE::StringKnobSummary();
    cerr << endl;
}

INSTLIB::ALIGN_CHECK align_check;
int 
main(int argc, char** argv)
{
    if (PIN_Init(argc, argv))
    {
        usage();
        return 1;
    }

    align_check.Activate();
    
    // Never returns
    PIN_StartProgram();

    // NOTREACHED
    return 0;
}
