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
using std::ofstream;
using std::string;
using std::endl;

static void OnExit(INT32, VOID *);

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool", "o", "exittool.out",
        "specify output file name");

ofstream OutFile;

int main(int argc, char * argv[])
{
    PIN_Init(argc, argv);

    OutFile.open(KnobOutputFile.Value().c_str());

    PIN_AddFiniFunction(OnExit, 0);

    PIN_StartProgram();
    return 0;
}


static void OnExit(INT32 code, VOID *v)
{
    OutFile << "Tool sees exit" << endl;
}
