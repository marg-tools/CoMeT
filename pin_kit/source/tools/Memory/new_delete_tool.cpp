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
#include <assert.h>
#include <iostream>
#include <cstdlib>

/*
  There was a memory leak in Pin when a tool did a lot of memory allocations and releases, and the application is
  multithreaded
  */

#define MAX_NUM_TH 1024

typedef struct {
   UINT64 *d;
   UINT64 pad[7];
} data_t;
data_t data_array[MAX_NUM_TH];

VOID doMemTest(THREADID threadid)
{
   assert(threadid < MAX_NUM_TH);
   data_array[threadid].d = new UINT64;
   delete data_array[threadid].d;
   return;
}

VOID insCallback(INS ins, void *v)
{
   INS_InsertCall(ins, IPOINT_BEFORE,
      AFUNPTR(doMemTest),
      IARG_THREAD_ID,
      IARG_END);
}

int main(int argc, char **argv)
{
   PIN_Init(argc,argv);
   INS_AddInstrumentFunction(insCallback, 0);
   PIN_StartProgram();
   return 0;
}
