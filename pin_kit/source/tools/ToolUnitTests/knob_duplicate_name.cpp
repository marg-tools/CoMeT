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
 * Knobs have a name, which is the text in the command-line (after the
 * dash) which is used to pass values to the knob.  Pin does not allow
 * developers to define several knobs with the same exact name.  This
 * test verifies this restriction in Pin tools.
 */

#include "pin.H"
using std::string;


KNOB<string> KnobTest1(KNOB_MODE_WRITEONCE, "pintool", "test", "",
    "Test knob #1 - checks the operation of 'write once' knobs");

KNOB<string> KnobTest2(KNOB_MODE_WRITEONCE, "pintool", "test", "",
    "Test knob #2 - checks the operation of 'write once' knobs");


int main(int argc, char * argv[])
{
    if (PIN_Init(argc, argv))
        return 1;

    PIN_StartProgram();
    return 0;
}

