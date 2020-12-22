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

#include "asm_macros.h"

DECLARE_FUNCTION(ReadFpContext)
NAME(ReadFpContext):
	fxsave (%rdi)
	ret

DECLARE_FUNCTION(WriteFpContext)
NAME(WriteFpContext):
	fxrstor (%rdi)
	ret
END_FUNCTION(WriteFpContext)

.global sched_yield

// void GetLock(long *mutex, long newVal)
DECLARE_FUNCTION(GetLock)
NAME(GetLock):
    push %rbp
    mov %rsp, %rbp
    xor %rax, %rax 
    
    // rdi - mutex
    // rsi - newVal

try_again:
    lock cmpxchg %rsi, (%rdi)
    je done
    push %rsi
    push %rdi
    call PLT_ADDRESS(sched_yield)
    pop %rdi
    pop %rsi
    jmp try_again
done:
    leave
    ret
END_FUNCTION(GetLock)

// void ReleaseLock(long *mutex)

DECLARE_FUNCTION(ReleaseLock)
NAME(ReleaseLock):
    push %rdi
    xor %rax, %rax
    lock xchg %rax, (%rdi) # put 0 in *mutex
    pop %rdi
    ret
END_FUNCTION(ReleaseLock)

// void InitLock(long *mutex)
DECLARE_FUNCTION(InitLock)
NAME(InitLock):
    push %rdi
    xor %rax, %rax
    lock xchg %rax, (%rdi) # put 0 in *mutex
    pop %rdi
    ret
END_FUNCTION(InitLock)
    
// extern "C" void SetXmmRegs(long v1, long v2, long v3);
// extern "C" void GetXmmRegs(long *v1, long *v2, long *v3);



DECLARE_FUNCTION(SetXmmRegs)
NAME(SetXmmRegs):
  movd %rdi, %xmm1
  movd %rsi, %xmm2
  movd %rdx, %xmm3
  ret
END_FUNCTION(SetXmmRegs)

DECLARE_FUNCTION(GetXmmRegs)
NAME(GetXmmRegs):
  movsd %xmm1, (%rdi)
  movsd %xmm2, (%rsi)
  movsd %xmm3, (%rdx)
  ret
END_FUNCTION(GetXmmRegs)
