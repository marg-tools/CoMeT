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
 * This tool excersizes the fetch_rtn_ins code when replaying an image load.
 */
#include <fstream>
#include <iostream>
#include <iomanip>

#include <string.h>
#include "pin.H"
using std::cerr;
using std::string;
using std::endl;

#ifdef TARGET_MAC
#define NAME(fun) "_" fun
#else
#define NAME(fun) fun
#endif

KNOB<string> KnobTestImage(KNOB_MODE_WRITEONCE,"pintool", "test-image", "", "Image to test");

VOID Image(IMG img, VOID *v)
{
    RTN foo = RTN_FindByName(img, NAME("foo"));
    ASSERTX(RTN_Valid(foo) || !IMG_IsMainExecutable(img));
    if (RTN_Valid(foo))
    {
        RTN_Open(foo);
        RTN_InsHead(foo);
        RTN_Close(foo);
    }
}



int main(int argc, char * argv[])
{
    PIN_InitSymbols();
    PIN_Init(argc, argv);

    // We will handle image load operations.
    PIN_SetReplayMode (REPLAY_MODE_IMAGEOPS);

    string testImage = KnobTestImage.Value();
    if (testImage.empty())
    {
        cerr << "ERROR: Must specify " << KnobTestImage.Cmd() << " to this PinTool" << endl;
        cerr << KNOB_BASE::StringKnobSummary();
        return 1;
    }
    // Creates artificial main image
    PIN_LockClient();
    PIN_ReplayImageLoad(testImage.c_str(), testImage.c_str(), 0x40000, REPLAY_IMAGE_TYPE_MAIN_EXE);
    PIN_UnlockClient();

    IMG_AddInstrumentFunction(Image, 0);

    // Never returns
    PIN_StartProgram();

    return 0;
}

