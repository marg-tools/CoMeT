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

#if defined (TARGET_WINDOWS)
#define EXPORT_SYM __declspec( dllexport ) 
#else
#define EXPORT_SYM extern
#endif


long x = 0;
EXPORT_SYM long Original( long one, long two )
{
    x += (two + one);
    //if (one != 1 || two != 2)
    //{
    //    printf ("got unexpected param value\n");
    //    exit (-1);
    //}
    return (x);
}

EXPORT_SYM long PreOriginal( long one, long two )
{
    x += (two - one);
    //if (one != 1 || two != 2)
    //{
    //    printf ("got unexpected param value\n");
    //    exit (-1);
    //}
    return (x);
}

