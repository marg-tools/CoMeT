/*BEGIN_LEGAL 
Intel Open Source License 

Copyright (c) 2002-2018 Intel Corporation. All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.  Redistributions
in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.  Neither the name of
the Intel Corporation nor the names of its contributors may be used to
endorse or promote products derived from this software without
specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE INTEL OR
ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
END_LEGAL */
    .text
    .align 4
.globl LoadYmm0
.type LoadYmm0, @function
LoadYmm0:
    mov     4(%esp), %ecx

    /*
     * This is "VMOVDQU ymm0, YMMWORD PTR [ecx]".  We directly specify the machine code,
     * so this test runs even when the compiler doesn't support AVX512.
     */
    .byte   0xc5, 0xfe, 0x6f, 0x01

.globl LoadYmm0Breakpoint
LoadYmm0Breakpoint:         /* Debugger puts a breakpoint here */
    ret

.globl LoadZmm0
.type LoadZmm0, @function
LoadZmm0:
    mov     4(%esp), %ecx

    /*
     * This is "VMOVUPD zmm0, ZMMWORD PTR [ecx]".  We directly specify the machine code,
     * so this test runs even when the compiler doesn't support AVX512.
     */
    .byte   0x62, 0xf1, 0xfd, 0x48, 0x10, 0x01

.globl LoadZmm0Breakpoint
LoadZmm0Breakpoint:         /* Debugger puts a breakpoint here */
    ret

.globl LoadK0
.type LoadK0, @function
LoadK0:
    mov     4(%esp), %ecx

    /*
     * This is "KMOVW k0, WORD PTR [ecx]".  We directly specify the machine code,
     * so this test runs even when the compiler doesn't support AVX512.
     */
    .byte   0xc5, 0xf8, 0x90, 0x01

.globl LoadK0Breakpoint
LoadK0Breakpoint:         /* Debugger puts a breakpoint here */
    ret
