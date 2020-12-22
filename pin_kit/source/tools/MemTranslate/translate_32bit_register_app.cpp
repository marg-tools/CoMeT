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

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>

int main()
{
    int result;

    // Allocate memory in the low 32 bit of the address space
    void* ptr_32bit = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_32BIT, -1, 0);
    if (NULL == ptr_32bit)
    {
        perror("mmap failed");
        return 1;
    }

    asm(
            "movq %1, %%rax\n"
            "movl $0xbadc0de, (%%rax)\n"
            "movl (%%eax), %%eax\n"
            "movl %%eax, %0\n"
            : "=m" (result)
            : "m" (ptr_32bit)
            : "%rax");
    printf("result = %x\n", result);
    return 0;
}
