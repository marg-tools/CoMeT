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

// Test an analysis routine that does an fxsave/fxstore. 

#include <iostream>
#include <stdio.h>
#include "pin.H"
using std::cerr;
using std::endl;

void my_print(int x)
{
#if defined(TARGET_IA32) || defined(TARGET_IA32E)
    static char buffer[2048];
    static char* aligned_bufp =reinterpret_cast<char*> 
                               (((reinterpret_cast<ADDRINT>(buffer) + 16) >> 4)<<4);

#if defined(PIN_GNU_COMPATIBLE)
    cerr << "Pin GNU compatible" << endl;
    asm volatile ("fxsave %0\n\t"
                  "emms"
                  : "=m"(*aligned_bufp));
#else
    __asm {
            push eax
            
            mov  eax, aligned_bufp
            fxsave [eax]
            
            pop eax
          }
#endif
#endif
    
    cerr << "my_print: " << x << endl;
    double y = x * 0.33445;
    cerr << "Done initializing y" << endl;
    cerr << y << endl;
    cerr << "Done with my_print" << endl;
    
#if defined(TARGET_IA32) || defined(TARGET_IA32E)
#if defined(PIN_GNU_COMPATIBLE)
    asm volatile ("fxrstor %0" :: "m"(*aligned_bufp));
#else
    __asm {
            push eax
            
            mov  eax, aligned_bufp
            fxrstor [eax]
            
            pop eax
          }
#endif
#endif
}

VOID ImageLoad(IMG img, VOID * v)
{
    RTN rtn;
    
    rtn = RTN_FindByName(img, "print");
    if (RTN_Valid(rtn))
    {
        RTN_Open(rtn);
        
        RTN_InsertCall(rtn, IPOINT_BEFORE,
                       (AFUNPTR)my_print,
                       IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                       IARG_END);

        RTN_Close(rtn);
    }
}

int main(int argc, char *argv[])
{
    PIN_InitSymbols();
    PIN_Init(argc, argv);
    
    IMG_AddInstrumentFunction(ImageLoad, 0);
    
    PIN_StartProgram();
    return 0;
}

