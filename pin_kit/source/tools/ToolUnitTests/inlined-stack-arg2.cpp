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


using std::string;
using std::cerr;
using std::endl;

LOCALVAR std::ofstream log_inl;

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE,         "pintool",
    "o", "inlined-stack-arg2.out", "output file");

#if defined(__cplusplus)
extern "C"
#endif
VOID Analysis_func (ADDRINT param);

#if defined(__cplusplus)
extern "C"
#endif
VOID Analysis_func_immed (ADDRINT immed);

#if defined(__cplusplus)
extern "C"
#endif
VOID Analysis_func_reg_overwrite (ADDRINT param);




INT32 Usage()
{
    cerr <<
        "This tests if the stack arguments are optimized as expected"
        "\n";

    cerr << endl;

    return -1;
}

VOID Instruction(INS ins, VOID *v)
{
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)Analysis_func,
#ifdef TARGET_IA32E // 4 dummy params in regs on Intel64
		           IARG_ADDRINT, 1,
				   IARG_ADDRINT, 2,
				   IARG_ADDRINT, 3,
				   IARG_ADDRINT, 4,
#endif
                   IARG_REG_VALUE, REG_GDX, 
				   IARG_END);

    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)Analysis_func_immed,
#ifdef TARGET_IA32E // 4 dummy params in regs on Intel64
		           IARG_ADDRINT, 1,
				   IARG_ADDRINT, 2,
				   IARG_ADDRINT, 3,
				   IARG_ADDRINT, 4,
#endif
                   IARG_ADDRINT, 0xdeadbeef, 
				   IARG_END);

    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)Analysis_func_immed,
#ifdef TARGET_IA32E // 4 dummy params in regs on Intel64
		           IARG_ADDRINT, 1,
				   IARG_ADDRINT, 2,
				   IARG_ADDRINT, 3,
				   IARG_ADDRINT, 4,
#endif
                   IARG_ADDRINT, 0x7eadbeef, 
				   IARG_END);

    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)Analysis_func_reg_overwrite,
#ifdef TARGET_IA32E // 4 dummy params in regs on Intel64
		           IARG_ADDRINT, 1,
				   IARG_ADDRINT, 2,
				   IARG_ADDRINT, 3,
				   IARG_ADDRINT, 4,
#endif
                   IARG_REG_VALUE, REG_GSI, 
				   IARG_END);
}

VOID Fini(INT32 code, VOID *v)
{
    log_inl  <<  "SUCCESS\n";
    log_inl.close();
}

int main(int argc, char *argv[])
{
    if( PIN_Init(argc,argv) )
    {
        return Usage();
    }

    string logfile =  KnobOutputFile.Value();

    log_inl.open(logfile.c_str());

    INS_AddInstrumentFunction(Instruction, 0);
    PIN_AddFiniFunction(Fini, 0);

    // Never returns
    PIN_StartProgram();
    
    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
