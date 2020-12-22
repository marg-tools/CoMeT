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
#include "instlib.H"

using namespace INSTLIB;

FOLLOW_CHILD follow;

INT32 Usage()
{
    cerr <<
        "This pin tool demonstrates use of FOLLOW_CHILD to inject pin in programs that call exec\n"
        "\n";

    cerr << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

// argc, argv are the entire command line, including pin -t <toolname> -- ...
int main(int argc, char * argv[])
{
    if( PIN_Init(argc,argv) )
    {
        return Usage();
    }

    follow.Activate();

    // Use the same prefix as our command line
    follow.SetPrefix(argv);
    
    // Start the program, never returns
    PIN_StartProgram();
    
    return 0;
}


