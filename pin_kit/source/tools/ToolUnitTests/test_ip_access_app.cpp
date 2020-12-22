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

/*
This tests the ability to handle the [REG_INST_PTR] memory operand (instruction pointer is base register
and no offset or index register). Also the ability to get the register value of the REG_INST_PTR
*/

#include <assert.h>
#include <stdio.h>
#include <string.h>

#if defined(__cplusplus)
extern "C"
#endif
void TestIpRead ();
#if defined(__cplusplus)
extern "C"
#endif
void TestIpWrite ();
#if defined(__cplusplus)
extern "C"
#endif
void Dummy ();

typedef void (*MY_FUNC_PTR)(void); 
typedef union
{
    MY_FUNC_PTR codePtr;
    char * dataPtr;
} MY_FUNC_PTR_CAST;

const size_t MAX_FUNC_SIZE = 8192;
/*!
 * Return size of the specified (foo or bar) routine
 */
size_t FuncSize(MY_FUNC_PTR func, MY_FUNC_PTR funcEnd)
{
    MY_FUNC_PTR_CAST cast;

    cast.codePtr = func;
    const char * start = cast.dataPtr;

    cast.codePtr = funcEnd;
    const char * end = cast.dataPtr;

    assert(end > start);
    assert(end - start <= MAX_FUNC_SIZE);
    return end - start;
}

/*!
 * Copy the TestIpWrite routine into a data buffer - because it contains a 
   mov [ip], 0x90
   and this write will cause an access violation if executed in the code segment
 */
void CopyAndExecuteTestIpWrite()
{
    static char staticBuffer[MAX_FUNC_SIZE];

    size_t size;
    size = FuncSize(TestIpWrite, Dummy);
    

    MY_FUNC_PTR_CAST cast;

    cast.codePtr = TestIpWrite;
    const void * funcAddr = cast.dataPtr;
    memcpy(staticBuffer, funcAddr, size);

    cast.dataPtr = static_cast<char *>(staticBuffer);
    MY_FUNC_PTR funcCopy = cast.codePtr;
    funcCopy();
}

int main(int argc, char *argv[])
{
    TestIpRead();
    CopyAndExecuteTestIpWrite();
    return 0;
}
