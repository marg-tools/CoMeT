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


/*! @file
 *  This is an example of probing RtlAllocateHeap
 */

#include "pin.H"
namespace WINDOWS
{
#include<Windows.h>
}
#include <iostream>

using std::hex;
using std::endl;
using std::cout;
using std::dec;
using std::flush;

VOID Before1( WINDOWS::PVOID hHeap, 
              WINDOWS::ULONG dwFlags, 
              WINDOWS::SIZE_T dwBytes )
{     
	cout << "Before 1: RtlAllocateHeap( " << hex << (ADDRINT)hHeap << ", " <<
		dwFlags << ", " << dwBytes << ")" << dec << endl << flush; 
}

void InsertProbe( IMG img, char * funcName)
{
    RTN allocRtn = RTN_FindByName(img, funcName);
    if (RTN_Valid(allocRtn) && RTN_IsSafeForProbedInsertion(allocRtn))
    {  
        cout << "RTN_InsertCallProbed on " << funcName << endl << flush;

        RTN_InsertCallProbed(allocRtn, IPOINT_BEFORE,
                             AFUNPTR(Before1),
                             IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                             IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                             IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
                             IARG_END);
    }    
}



/*
 * process_loaded_image: Called every time when new image is loaded.
 */
static VOID process_loaded_image(IMG image, VOID *value)
{
    if ( !IMG_Valid(image) )
        return;
    
    InsertProbe( image, "RtlAllocateHeap");
    
}



int main(int argc, char **argv)
{
    PIN_InitSymbols();  
    if ( PIN_Init(argc, argv) )
        return -1;

    IMG_AddInstrumentFunction(process_loaded_image, 0); 
    PIN_StartProgramProbed();
}

