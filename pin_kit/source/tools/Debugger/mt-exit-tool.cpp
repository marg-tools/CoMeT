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
    "mt-exit-tool.out", "Output file");

std::ofstream Out;


int main(int argc, char * argv[])
{
    PIN_Init(argc, argv);

    Out.open(KnobOut.Value().c_str());
    Out << std::dec << PIN_GetPid() << std::endl;
    Out.close();

    PIN_StartProgram();
    return 0;
}
