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

#define __ISO_C_VISIBLE 1999
#ifdef NDEBUG
# undef NDEBUG
#endif
#include <assert.h>
#include <stdlib.h>
#include <execinfo.h>
#include <iostream>
using std::cout;
using std::endl;


extern "C" void qux()
{
    cout << "qux" << endl;
}

extern "C" void baz()
{
    void* buf[128];
    int nptrs = backtrace(buf, sizeof(buf)/sizeof(buf[0]));
    assert(nptrs > 0);
    char** bt = backtrace_symbols(buf, nptrs);
    assert(NULL != bt);
    for (int i = 0; i < nptrs; i++)
    {
        cout << bt[i] << endl;
    }
    free(bt);
}

extern "C" void bar()
{
    baz();
    qux();
}

extern "C" __attribute__((visibility("default"))) void foo();

extern "C" void foo()
{
    bar();
    qux();
}
