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

#include <string.h>
#include <stdio.h>

char str1[] = "foo";
char str2[] = "foo";
char str3[] = "not_foo";

int main(int argc, char *argv[])
{
    char *p_str2 = str2;
    char *p_str3 = str3;

    if (strcmp(str1, p_str2) == 0)
         fprintf(stderr, " string equals to foo\n");
    if (strcmp(str1, p_str3) == 0)
        fprintf(stderr, " string isn't equal to foo\n");
    return 0;
}
