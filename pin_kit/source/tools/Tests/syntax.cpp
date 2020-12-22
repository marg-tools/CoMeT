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
 *  Print the first INS according to all syntax options.
 */

#include <iostream>
#include <fstream>
#include "pin.H"
using std::cout;
using std::endl;


BOOL test = true;

VOID Inst(INS ins, VOID * v)
{
    if (!test)
        return;
    test = false;

    cout << "DEFAULT: " << INS_Disassemble(ins) << endl;
    PIN_SetSyntaxATT();
    cout << "ATT: " << INS_Disassemble(ins) << endl;
    PIN_SetSyntaxIntel();
    cout << "INTEL: " << INS_Disassemble(ins) << endl;
    PIN_SetSyntaxXED();
    cout << "XED: " << INS_Disassemble(ins) << endl;
}

int main(INT32 argc, CHAR **argv)
{
    PIN_Init(argc, argv);
    
    INS_AddInstrumentFunction(Inst, 0);
    
    // Never returns
    PIN_StartProgram();
    
    return 0;
}
