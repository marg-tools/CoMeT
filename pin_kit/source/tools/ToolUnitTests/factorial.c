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

#ifdef TARGET_WINDOWS
#define EXPORT_CSYM __declspec( dllexport )
#else
#define EXPORT_CSYM 
#endif

EXPORT_CSYM int factorial(int n)
{
    if ((n < 0) || (n > 30)) {
        return 0;
    } else if (n == 0) {
        return 1;
    } else {
        return n * factorial(n-1);
    }
}

int main(int argc, char *argv[])
{
    int n;
    if (argc != 2) {
       fprintf(stderr, "Usage: %s number_string\n", argv[0]);
       return 1;
    }
    n = atoi(argv[1]);
    fprintf(stdout, "%d!=%d\n", n, factorial(n));
    return 0;
}
