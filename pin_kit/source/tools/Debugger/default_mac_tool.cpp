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
 * Default tool to be used for Debugger tests in macOS for tests which don't have their own tool.
 * This tool only initialize basic stuff without any instrumentation and continue to run the program.
 * This is needed since currently the only way to place breakpoint in macOS is to to process the application image and today
 * we do that only when there is a tool (conceptually if there is no tool then we don't have any instrumentation,
 * no analysis routines and so on, although in probe mode we do that, need to check it).
 * The data of the main image is being passed to the lldb front end which use
 * this information in order to be able to place breakpoints and so on.
 */

#include "pin.H"


int main(int argc, char *argv[])
{
    // Make sure we parse the application image
    PIN_InitSymbols();
    PIN_Init(argc, argv);


    PIN_StartProgram();
    return 0;
}

