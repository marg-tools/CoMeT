/*
 * Copyright 2002-2019 Intel Corporation.
 * 
 * This software and the related documents are Intel copyrighted materials, and your
 * use of them is governed by the express license under which they were provided to
 * you ("License"). Unless the License provides otherwise, you may not use, modify,
 * copy, publish, distribute, disclose or transmit this software or the related
 * documents without Intel's prior written permission.
 * 
 * This software and the related documents are provided as is, with no express or
 * implied warranties, other than those that are expressly stated in the License.
 */

/*
** <COMPONENT>: asm
** <FILE-TYPE>: component public header
*/

#ifndef ASM_MASM_X86_H
#define ASM_MASM_X86_H


#if defined(HOST_IA32)

#define ASM_FILEBEGIN()  \
.686 ASM_NEWLINE \
.xmm ASM_NEWLINE \
.model flat,c

#else
#   define ASM_FILEBEGIN()
#endif

#define ASM_FILEEND()   END


#define ASM_FUNCBEGIN(name, rtype, args)    \
    .CODE ASM_NEWLINE                       \
    ALIGN 4 ASM_NEWLINE                     \
    ASM_NAME(name) PROC

#define ASM_FUNCEND(name)   ASM_NAME(name) ENDP

#define ASM_HEX(val)    0##val##h
#define ASM_NAME(name)  name

#define ASM_LABDEF(x)   $l##x##:
#define ASM_LABF(x)     $l##x
#define ASM_LABB(x)     $l##x
#define ASM_GLABDEF(x)  ASM_NAME(x):

#define ASM_BYTE()      BYTE PTR
#define ASM_WORD()      WORD PTR
#define ASM_DWORD()     DWORD PTR
#define ASM_QWORD()     QWORD PTR

#endif /*file guard*/
