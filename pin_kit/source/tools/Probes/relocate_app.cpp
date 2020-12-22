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
extern "C" void relocatable_1();
extern "C" int relocatable_1a();
extern "C" void relocatable_2();
extern "C" void relocatable_3();
extern "C" void non_relocatable_1();
extern "C" void non_relocatable_2();

int main()
{
    relocatable_1();
    
    int x = relocatable_1a();
    if (x != (int)0xdeadbeef)
    {
        fprintf (stderr, "***Error relocatable_1a returned wrong value %x\n", x);
        return(-1);
    }
    
    relocatable_2();
    relocatable_3();
    return 0;
}

