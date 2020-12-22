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

#include <stdlib.h>

#if !defined(__GNUC__)
extern void movdqa_test(char* p);
#endif

int main(int argc, char** argv)
{
    char a[1000];

    /* get in to the buffer and then align it by 16 */
    static const size_t align16_mask = (16 - 1);
    /* Integer type size_t defined to have size of pointer */
    char* b = (char*)(((size_t)a + align16_mask) & ~align16_mask);

    /* generate one aligned move and one unaligned move. The alignchk tool
     * should catch the latter one. */

#if defined(__GNUC__)
    char* c = b + 1;
    asm volatile("movdqa %%xmm0, %0" : "=m" (*b)  : : "%xmm0"); 
    asm volatile("movdqa %%xmm0, %0" : "=m" (*c)  : : "%xmm0"); 
#else
    movdqa_test(b);
#endif
    
}
