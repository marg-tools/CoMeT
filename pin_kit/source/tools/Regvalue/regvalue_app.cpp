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

#include "regvalues.h"

#ifdef TARGET_WINDOWS
#define EXPORT_SYM __declspec( dllexport )
#else
#define EXPORT_SYM
#endif


/////////////////////
// EXTERNAL FUNCTIONS
/////////////////////

// ChangeRegsWrapper saves the registers that are about to be changed.
// Then it calls ChangeRegs. The tool intercepts this call and replaces
// it with its own function which actually changes the registers.
// The wrapper then calls SaveRegsToMem which stores the tool-modified
// values to memory and allows the tool to verify them.
// Finally, the original register values are restored.
extern "C" void ChangeRegsWrapper() ASMNAME("ChangeRegsWrapper");


/////////////////////
// UTILITY FUNCTIONS
/////////////////////

// The SaveAppPointers() function is an empty function which is used by the tool to save pointers
// to the application's modified register values.
// These values will be set in the SaveRegsToMem() function (see the changeRegs_<arch> assembly file).
extern "C" EXPORT_SYM void SaveAppPointers(unsigned char* agprptr, unsigned char* astptr,
                                           unsigned char* axmmptr, unsigned char* aymmptr,
                                           unsigned char* azmmptr, unsigned char* aopmaskptr)
{
}


/////////////////////
// MAIN FUNCTION
/////////////////////

int main()
{
    SaveAppPointers(agprval, astval, axmmval, aymmval, azmmval, aopmaskval);
    ChangeRegsWrapper();
    return 0;
}
