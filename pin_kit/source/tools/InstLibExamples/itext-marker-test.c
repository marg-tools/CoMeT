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

int main() {
    int i;
    asm volatile(".byte 0x0f, 0x1f, 0xF3");
    for(i=0;i<10;i++)  
        ;
    asm volatile(".byte 0x0f, 0x1f, 0xF4");
    return 0;
}
