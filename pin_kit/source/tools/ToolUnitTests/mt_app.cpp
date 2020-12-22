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
 * A simple MT application.
 */

#include <string>
#include <iostream>
#include "../Utils/threadlib.h"
using std::flush;
using std::cerr;
using std::endl;

#if defined(TARGET_WINDOWS)
#define EXPORT_CSYM extern "C" __declspec( dllexport )
#else
#define EXPORT_CSYM extern "C"
#endif


/*!
 * The tool intercepts this function and flushes the Code Cache. 
 */
volatile unsigned numFlushes = 0;
EXPORT_CSYM void DoFlush()
{
    ++numFlushes;
}

void * ThreadProc(void * arg)
{
    DelayCurrentThread(1000); 
    return 0;
}

int main(int argc, char *argv[])
{
    const int numThreads = 3;
    THREAD_HANDLE threads[numThreads];
      
    for (int i = 0; i < numThreads; i++)
    {
        if (!CreateOneThread(&threads[i], ThreadProc, 0))
        {
            cerr << "CreateOneThread failed" << endl << flush;
        }
    }

    for (int i = 0; i < numThreads; i++)
    {
        if (!JoinOneThread(threads[i]))
        {
            cerr << "JoinOneThread failed" << endl << flush;
        }
    }

    cerr << "All application's threads joined" << endl << flush;

    // Trigger the Code Cache flush
    DoFlush();
    DelayCurrentThread(1000); 
    
    cerr << "Application is exiting" << endl << flush;

    return 0;
}
