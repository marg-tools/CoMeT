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

#include "pin.H"
#include <fstream>
using std::ofstream;
using std::endl;

UINT64 nops = 0;
ofstream* out;
VOID Fini(INT32 code, VOID* v) 
{
    *out << "NOPS: " << nops << endl;
    out->close();
}


    
VOID Instruction(INS ins, VOID *v)
{
    if (INS_IsNop(ins))
    {
        *out << INS_Disassemble(ins) << endl;
        nops++;
    }
}


int main(int argc, char * argv[])
{
    PIN_Init(argc, argv);
    out = new ofstream("nops.out");

    INS_AddInstrumentFunction(Instruction, 0);
    PIN_AddFiniFunction(Fini, 0);
    
    // Never returns
    PIN_StartProgram();
    
    return 0;
}
