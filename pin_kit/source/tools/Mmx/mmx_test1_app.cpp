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
extern "C" int MMXSequence (unsigned int a, unsigned int b, unsigned int c, UINT64 *aConcaTb);

int main ()
{
    UINT64 aConcaTb;
    UINT32 *ptr  = (UINT32 *)(&aConcaTb);
    UINT32 *ptr1 = ptr+1;
    unsigned int res = MMXSequence(0xdeadbeef, 0xbaadf00d, 0xfeedf00d, &aConcaTb);
    printf ("res is %x  aConcaTb is %x %x\n", res, (*ptr), *(ptr1));
    if (res != 0x3a061f04)
    {
        fprintf (stderr, "***Error unexpected value of res\n");
        return (1);
    }
    if (*ptr != 0xdeadbeef)
    {
        fprintf (stderr, "***Error unexpected value of *ptr\n");
        return (1);

    }
    if (*ptr1 != 0xbaadf00d)
    {
        fprintf (stderr, "***Error unexpected value of *ptr1\n");
        return (1);

    }
    return (0);
}

