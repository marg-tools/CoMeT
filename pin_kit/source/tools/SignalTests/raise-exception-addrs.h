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

#ifndef RAISE_EXCEPTION_ADDRS_H
#define RAISE_EXCEPTION_ADDRS_H

/*
 * Labels for various instructions that raise exceptions.
 */
typedef struct {
    char *_unmappedRead;
    char *_unmappedReadAddr;
    char *_unmappedWrite;
    char *_unmappedWriteAddr;
    char *_inaccessibleRead;
    char *_inaccessibleReadAddr;
    char *_inaccessibleWrite;
    char *_inaccessibleWriteAddr;
    char *_misalignedRead;
    char *_misalignedWrite;
    char *_illegalInstruction;
    char *_privilegedInstruction;
    char *_integerDivideByZero;
    char *_integerOverflowTrap;
    char *_boundTrap;
    char *_x87DivideByZero;
    char *_x87Overflow;
    char *_x87Underflow;
    char *_x87Precision;
    char *_x87InvalidOperation;
    char *_x87DenormalizedOperand;
    char *_x87StackUnderflow;
    char *_x87StackOverflow;
    char *_x87MultipleExceptions;
    char *_simdDivideByZero;
    char *_simdOverflow;
    char *_simdUnderflow;
    char *_simdPrecision;
    char *_simdInvalidOperation;
    char *_simdDenormalizedOperand;
    char *_simdMultipleExceptions;
    char *_breakpointTrap;
} RAISE_EXCEPTION_ADDRS;

#endif
