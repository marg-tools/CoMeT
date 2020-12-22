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

/* each iteration of the loop changes the code for the next iteration */
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>

unsigned int a = 0;
int  i;
int main(void)
{
    void *p;
    int  ret;

l1:
    p = &&l1;
    p = (char*)((int)p & 0xFFFFF000);
    
    ret =  mprotect(p, 4096, PROT_WRITE | PROT_READ | PROT_EXEC);
    if (ret != 0) {
        perror("mprotect");
        return -1;
    }
    for(i = 0; i < 1000; i++) {
        __asm__ __volatile__ (
            "movl a, %%eax
l3:         movl $1, %%ecx
l2:         incl %%eax
            loop l2
            movl %%eax, a
            movl i, %%eax
            incl %%eax
            movl $l3, %%ebx
            movl %%eax, 1(%%ebx)"
            :::"%ecx", "%ebx", "%eax"
        );
    }

    if (a == 499501)
        printf("Success!\n");
    else
        printf("Failed! a = %i\n", a);

    return 0;
}
