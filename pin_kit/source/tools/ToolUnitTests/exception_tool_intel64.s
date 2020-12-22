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

.text
.global ToolRaiseAccessInvalidAddressException
.type ToolRaiseAccessInvalidAddressException, @function
.global ToolCatchAccessInvalidAddressException
.type ToolCatchAccessInvalidAddressException, @function
.global ToolIpAccessInvalidAddressException
.type ToolIpAccessInvalidAddressException, @function

## ADDRINT ToolRaiseAccessInvalidAddressException(ADDRINT* addr , ADDRINT value);

ToolRaiseAccessInvalidAddressException:
    push %rbp
    mov %rsp, %rbp
    mov %rdi, %rax # addresses array
    # value in %rsi
    mov (%rax), %rdi
try_again:
ToolIpAccessInvalidAddressException:
    mov %rsi, (%rdi) # *addr = value - if addr is invalid, exception is raised
    leave
    ret

ToolCatchAccessInvalidAddressException:
    mov 8(%rax), %rdi
    jmp try_again
    

.text
.global ToolRaiseIntDivideByZeroException
.global ToolIpIntDivideByZeroException

# ADDRINT ToolRaiseIntDivideByZeroException(ADDRINT catch_ptr, ADDRINT exception_code)

.type ToolRaiseIntDivideByZeroException, @function
ToolRaiseIntDivideByZeroException:
    push %rbp
    mov %rsp, %rbp
    push %rbx # save ebx
    mov %rdi, %rbx # fptr
    # except code in %rsi
    push %rsi
    xor %rax, %rax
ToolIpIntDivideByZeroException:
    idiv %rax
    pop %rax
    pop %rbx
    leave
    ret
    
.global ToolCatchIntDivideByZeroException

.type ToolCatchIntDivideByZeroException, @function
ToolCatchIntDivideByZeroException:
    pop %rax #exception code -> rax
    pop %rbx
    leave
    ret
    
