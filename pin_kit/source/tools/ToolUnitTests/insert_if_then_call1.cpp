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
 *  Pin Tool for testing the correctness of "INS_InsertThenCall" function.
 */

#include "pin.H"
#include <iostream>
#include <fstream>
#include <string.h>
using std::cerr;
using std::string;
using std::endl;

/* ===================================================================== */
/* Commandline Switches */
/* ===================================================================== */

LOCALVAR std::ofstream out;

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "insert_if_then_call1.out", "Output file");


/* ===================================================================== */

static ADDRINT IfFunction()
{
    return TRUE;
}

static VOID ThenFunction (BOOL first)
{
    //do nothing
}



/* ===================================================================== */

VOID Instruction(INS ins, VOID *v)
{
    //Should cause an error since Pin does not support IPOINT_ANYWHERE with the function: "INS_InsertThenCall"
    INS_InsertIfCall(ins, IPOINT_BEFORE , (AFUNPTR)IfFunction, IARG_END);
    INS_InsertThenCall(ins, IPOINT_ANYWHERE, (AFUNPTR)ThenFunction, IARG_END);
}


/* ===================================================================== */
/* Utilities                                                             */
/* ===================================================================== */

/*!
*  Print out help message.
*/

INT32 Usage()
{
	/* Knobs automate the parsing and management of command line switches. 
     * A command line contains switches for Pin, the tool, and the application. 
     * The knobs parsing code understands how to separate them. 
     */
    cerr << KNOB_BASE::StringKnobSummary() << endl; //   Print out a summary of all the knobs declare

    return -1;
}


/* ===================================================================== */

int main(int argc, char *argv[])
{
    if( PIN_Init(argc,argv) )
    {
        return Usage();
    }

    INS_AddInstrumentFunction(Instruction, 0);

    // Never returns
    PIN_StartProgram();
    
    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
