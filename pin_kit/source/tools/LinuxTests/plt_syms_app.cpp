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

#include <cstdio>
#include <cstring>
#include <unistd.h>


int main()
{
    char printf_string[] = "printing using printf\n";
    char write_string[] = "printing using write\n";

    printf("%s", printf_string);
    fflush(stdout);

    write(STDOUT_FILENO, write_string, strlen(write_string));

    return 0;
}
