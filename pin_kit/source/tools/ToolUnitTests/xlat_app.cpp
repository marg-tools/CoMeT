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

#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <iostream>

extern "C" int test_xlat (void* buffer);

#define BUFFSIZE 1024

// This application allocates a buffer in the lower 2 GB of the process address space
// so that the address can be referenced with both 64 bit registers and 32 bit registers.
// The buffer is initialized for debugging purposes.
int main (int argc, char *argv[])
{
    void* buffer = mmap(    (void*)0x1000,                  // page aligned, lowest possible
                            BUFFSIZE,                       // length
                            PROT_READ|PROT_WRITE,           // protection
                            MAP_32BIT|MAP_PRIVATE|MAP_ANON, // flags
                            -1,                             // fd
                            0);                             // offset
    assert(buffer != NULL);
    std::cerr << "mmap returned address " << std::hex << buffer << std::endl;
    memset(buffer, 1, BUFFSIZE);
    test_xlat(buffer);
    return(0);
}
