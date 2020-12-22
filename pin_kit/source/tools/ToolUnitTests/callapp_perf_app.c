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

// This little application is used to test calling application functions.
//
#include <stdio.h>
#include <stdlib.h>

#if defined (TARGET_WINDOWS)
#define EXPORT_SYM __declspec( dllexport ) 
#else
#define EXPORT_SYM extern
#endif

EXPORT_SYM long Original( long one, long two );
EXPORT_SYM long PreOriginal( long one, long two );


int main()
{
    long res;
    int i;
    
    PreOriginal(6, 8);
    for (i=0; i<1000000; i++)
    {
        res = Original(6, 8);
    }
    if (((unsigned int)(res)) != (unsigned int)(0x2dc6c1))
    {
        printf ("***ERROR res %lx is unexpected\n", res);
        exit (-1);
    }
    return 0;
}
