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

#include <windows.h>
#include <stdio.h>

__declspec(dllexport) __declspec(naked) int __fastcall foo(int val)
{
    __asm {
        test ecx,ecx
        jz L
        mov eax, 2
        ret
L:
        mov eax, 5
        ret
    }
}

int main()
{
    // Should print "7"
    printf("%d\n", foo(0) + foo(!0));

    return 0;
}
