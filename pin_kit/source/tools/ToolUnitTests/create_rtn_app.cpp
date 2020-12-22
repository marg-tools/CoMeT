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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <cstdlib>
using std::cout;
using std::endl;

#if defined(TARGET_LINUX)
# define DATA_SECTION(secName) __attribute__ ((section (secName)))
# define SECTION_END
#elif defined(TARGET_MAC)
# define DATA_SECTION(secName) __attribute__ ((section ("__DATA,"secName)))
# define SECTION_END
#else
# define PUSH_SECTIONS__ __pragma(code_seg(push)) __pragma(data_seg(push)) __pragma(const_seg(push))
# define POP_SECTIONS__  __pragma(code_seg(pop))  __pragma(data_seg(pop))  __pragma(const_seg(pop))
# define DATA_SECTION(secName) PUSH_SECTIONS__  __pragma(data_seg(secName))
# define SECTION_END           POP_SECTIONS__
#endif


static int Proc1();
static int Proc2();

#if _MSC_VER && !__INTEL_COMPILER
#pragma code_seg(push)
#pragma code_seg("mySpecialSegment$a")
#endif
int main(int argc, char *argv[])
{
  cout << "Hello, world!" << endl;

  Proc1();
  Proc2();

  return EXIT_SUCCESS;
}

// We will use probes on the following functions, so their first BBL
// should be long enough to avoid jumps to our trampoline code, even
// when the compiler uses optimizations.
#if _MSC_VER && !__INTEL_COMPILER
#pragma code_seg("mySpecialSegment$b")
#endif
int Proc1()
{
    int n = 15;
    int i = 0;
    for (; i<10; i++)
    {
        cout << ".";
        n--;
    }
    cout << endl;
    return i + n;
}
#if _MSC_VER && !__INTEL_COMPILER
#pragma code_seg("mySpecialSegment$c")
#endif
int Proc2()
{
    int n = 15;
    int i = 0;
    for (; i<10; i++)
    {
        cout << ".";
        n++;
    }
    cout << endl;
    return n - i;
}
#if _MSC_VER && !__INTEL_COMPILER
#pragma code_seg(pop)
#endif


DATA_SECTION(".fTable")
const char *ptr[2] = { (const char *)&Proc1, (const char *)&Proc2 };
SECTION_END
