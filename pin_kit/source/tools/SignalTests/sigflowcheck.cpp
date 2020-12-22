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

#include <fstream>
#include "pin.H"
using std::dec;
using std::ofstream;
using std::hex;
using std::string;
using std::endl;

static void OnSig(THREADID, CONTEXT_CHANGE_REASON, const CONTEXT *, CONTEXT *, INT32, VOID *);
static void OnEnd(INT32, VOID *);


std::vector<ADDRINT> Stack;

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool", "o", "inscount.out",
        "specify output file name");

ofstream OutFile;

INT32 Usage()
{
    OutFile << endl << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

int main(int argc, char * argv[])
{
    if (PIN_Init(argc, argv)) return Usage();

    OutFile.open(KnobOutputFile.Value().c_str());

    PIN_AddContextChangeFunction(OnSig, 0);
    PIN_AddFiniFunction(OnEnd, 0);

    PIN_StartProgram();
    return 0;
}


static void OnSig(THREADID threadIndex, CONTEXT_CHANGE_REASON reason, const CONTEXT *ctxtFrom,
    CONTEXT *ctxtTo, INT32 sig, VOID *v)
{
    switch (reason)
    {
    case CONTEXT_CHANGE_REASON_SIGNAL:
        Stack.push_back(PIN_GetContextReg(ctxtFrom, REG_INST_PTR));
        break;

    case CONTEXT_CHANGE_REASON_SIGRETURN:
      {
        ADDRINT savedPC = Stack.back();
        ADDRINT returnPC = PIN_GetContextReg(ctxtTo, REG_INST_PTR);
        if (savedPC != returnPC)
        {
            OutFile << "Handler does not return to original location: saved=" << hex << savedPC <<
                " return=" << returnPC << dec << endl;
        }
        Stack.pop_back();
        break;
      }
    default:
        OutFile << "Unexpected CONTEXT_CHANGE_REASON " << reason << ", exiting the test." << endl;
        PIN_ExitProcess(1);
        break;
    }
}

static void OnEnd(INT32 code, VOID *v)
{
    OutFile << "Program exitted with " << Stack.size() << " signal frames pending" << endl;
}
