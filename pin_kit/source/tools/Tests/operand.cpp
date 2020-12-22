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

#include <iostream>
#include <fstream>
using std::ofstream;
using std::endl;

ofstream dis("operand.out");

VOID Instruction(INS ins, VOID *v)
{
    INT32 count = INS_OperandCount(ins);
    
    for (INT32 i = 0; i < 5; i++)
    {
        if (i >= count)
        {
            dis << "        ";
            continue;
        }
        
        else if (INS_OperandIsAddressGenerator(ins, i))
            dis << "AGN";
        else if (INS_OperandIsMemory(ins, i))
        {
            dis << "MEM";
            dis << " " << REG_StringShort(INS_OperandMemoryBaseReg(ins, i));
        }
        else if (INS_OperandIsReg(ins, i))
            dis << "REG";
        else if (INS_OperandIsImmediate(ins, i))
            dis << "IMM";
        else if (INS_OperandIsBranchDisplacement(ins, i))
            dis << "DSP";
        else
            dis << "XXX";

        if (INS_OperandIsImplicit(ins, i))
            dis << ":IMP ";
        else
            dis << "     ";
                
        
    }

    dis << INS_Disassemble(ins) << endl;
}

int main(int argc, char * argv[])
{
    PIN_Init(argc, argv);

    INS_AddInstrumentFunction(Instruction, 0);
    
    // Never returns
    PIN_StartProgram();
    
    return 0;
}
