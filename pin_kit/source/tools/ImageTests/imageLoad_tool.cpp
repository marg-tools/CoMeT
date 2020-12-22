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
 * This tool verifies that the registered image callback is being called for images that are loaded after attaching Pin in probe mode.
 */

#include "pin.H"
#include <fstream>
using std::ofstream;
using std::string;
using std::endl;

/* ===================================================================== */
/* Commandline Switches */
/* ===================================================================== */

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "imageLoad.out", "specify file name");

ofstream TraceFile;
/* ===================================================================== */

int afterAttachProbe(void)
{
    return 1;
}

static VOID imageLoad(IMG img, VOID *v)
{
    TraceFile <<  "in image callback of image: " << IMG_Name(img).c_str() << endl;
    if ( IMG_IsMainExecutable(img))
    {
        RTN rtn = RTN_FindByName(img, "AfterAttach");
        if (RTN_Valid(rtn))
        {
            RTN_ReplaceProbed(rtn, AFUNPTR(afterAttachProbe));
        }
    }
}
int main(int argc, char * argv[])
{
    PIN_InitSymbols();

    // Initialize pin
    PIN_Init(argc, argv);

    TraceFile.open(KnobOutputFile.Value().c_str());
    IMG_AddInstrumentFunction(imageLoad, 0);

    // Start the program, never returns
    PIN_StartProgramProbed();

    return 0;
}
