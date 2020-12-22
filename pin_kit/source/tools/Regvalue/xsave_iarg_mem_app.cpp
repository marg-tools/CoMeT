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

#include <cstring>
#include <cstdio>

#ifdef TARGET_WINDOWS
# define ASMNAME(name)
# define ALIGN64 __declspec(align(64))
#else
# define ASMNAME(name) asm(name)
# define ALIGN64 __attribute__ ((aligned (64)))
#endif

#ifdef TARGET_IA32
typedef long ADDRINT;
#define ADDRINT_FORMAT "%lx"
#else
typedef long long ADDRINT;
#define ADDRINT_FORMAT "%llx"
#endif

/////////////////////
// EXTERNAL FUNCTIONS
/////////////////////

extern "C" void DoXsave() ASMNAME("DoXsave");
extern "C" void DoXsaveOpt() ASMNAME("DoXsaveOpt");
extern "C" void DoXrstor() ASMNAME("DoXrstor");


/////////////////////
// GLOBAL VARIABLES
/////////////////////

extern "C"
{
// the current size is large enough for avx512
unsigned char ALIGN64 xsaveArea[2688] ASMNAME("xsaveArea");
ADDRINT flags ASMNAME("flags");
}

ADDRINT checkedFlags [10] = {
                            0x00, /* none */
                            0x03, /* only legacy */
                            0x04, /* only avx    */
                            0x07, /* combo1 legacy + AVX */
                            0x18, /* only BND    */
                            0x1c, /* combo2 BND + AVX */
                            0xc4, /* combo3 some AVX512 + AVX */
                            0xd5, /* combo4 some AVX512 + some BND + AVX + some legacy */
                            0xe0, /* only AVX512 */
                            0xff  /* all  */
                          };

int main(int argc, const char* argv[])
{
    memset(xsaveArea, 0, sizeof(xsaveArea));

    for (int i=0; i<4; i++) {
      flags = checkedFlags[i];

      DoXsave(); // get the register value before the change
      printf("XSAVE on 0x" ADDRINT_FORMAT "\n", (ADDRINT)xsaveArea);

      DoXsaveOpt(); // get the register value before the change
      printf("XSAVEOPT on 0x" ADDRINT_FORMAT "\n", (ADDRINT)xsaveArea);

      DoXrstor(); // restor the register value
      printf("XRSTOR on 0x" ADDRINT_FORMAT "\n", (ADDRINT)xsaveArea);
   }


   return 0;
}
