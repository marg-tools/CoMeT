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

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

#ifdef TARGET_WINDOWS
#define NOINLINE __declspec(noinline)
#define IMPORT EXTERNC __declspec(dllimport)
#define EXPORT_CSYM EXTERNC __declspec(dllexport)
#else
#define NOINLINE __attribute__((noinline))
#define IMPORT EXTERNC 
#define EXPORT_CSYM EXTERNC
#endif

extern int IMPORT one();

int EXPORT_CSYM NOINLINE two() {
    return 2;
}

int (*two_ptr)(void);

int EXPORT_CSYM main(void)
{
    two_ptr = two;
    printf("%d\n", one());
    printf("%d\n", (*two_ptr)());
    return 0;
}
