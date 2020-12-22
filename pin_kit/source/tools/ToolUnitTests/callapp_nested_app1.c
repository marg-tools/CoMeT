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

EXPORT_SYM long Original2( long param1, long param2 )
{
    x += (param2 + param1);
    return (x);
}

EXPORT_SYM long Original1( long param1, long param2 )
{
    int val = Original2(param1, param2);
    x += (param2 + param1 + val);
    return (x);
}

EXPORT_SYM long PreOriginal( long param1, long param2 )
{
    x += (param2 + param1);
    return (x);
}

