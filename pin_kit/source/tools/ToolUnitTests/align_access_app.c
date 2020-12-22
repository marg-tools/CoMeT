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
#include <stdlib.h>
#include <memory.h>

#if defined(TARGET_WINDOWS)
#define EXPORT_CSYM  __declspec( dllexport )
#else
#define EXPORT_CSYM 
#endif

typedef union {
    unsigned char *p;
    unsigned long l;
} PTOL;

EXPORT_CSYM unsigned long ptr2long(unsigned char *ptr)
{
    PTOL cast;
    cast.p = ptr;
    return cast.l;
}

EXPORT_CSYM void set_value(unsigned char *buf, unsigned int val)
{
    unsigned int *arr = (unsigned int *)buf;
    arr[0] = val;
}

EXPORT_CSYM int check_align(unsigned char *ptr)
{
    if (ptr2long(ptr) % 16)
        return 1;

    return 0;
}

int main()
{
    // align the buffer on 16 and call set value in a loop
    unsigned char buff[1000];
    unsigned char *ptr = buff + (16 - (ptr2long(buff) % 16));
    int i;

    memset(buff, 0, 1000);

    printf("Base pointer: %p\n", ptr);
    for (i = 0; i < 20; i++)
        set_value(ptr + 16 * i, 1);

    for (i = 0; i < 1000; i++)
    {
        if (buff[i] && check_align(&buff[i]))
        {
            printf("Align check failed on %p\n", &buff[i]);
            exit(1);
        }
    }

    printf("Align check ok\n");
    exit(0);
}
