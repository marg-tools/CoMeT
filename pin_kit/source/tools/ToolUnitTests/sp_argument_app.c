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

void * current_sp_value(void* arg1,
                        void* arg2,
                        void* arg3,
                        void* arg4,
                        void* arg5,
                        void* arg6,
                        void* arg7,
                        void* arg8,
                        void* arg9)
{
    // Assume arg9 is on stack. Return SP value at entry to the function.
    // It is assumed that stack slot of size sizeof(void*) corresponds to every argument.
    // This is relevant to any X86 and Intel(R) 64 calling conventions.
    // The expression returns address of return IP slot.
    return &arg9 - 9;
}

// Replaced by Pin instrumentation
int check_sp_value(void* arg)
{
    if (arg != 0) return 0;
    return 1;
}
int main()
{
    void * current_sp = current_sp_value(0, 0, 0, 0, 0, 0, 0, 0, 0);
    return check_sp_value(current_sp);
}
