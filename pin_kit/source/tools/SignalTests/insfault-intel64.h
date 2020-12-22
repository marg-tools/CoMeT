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

#ifndef INSFAULT_INTEL64_H
#define INSFAULT_INTEL64_H

#include "types.h"


// The assembly file sets these to the expected values for each register.
//
extern "C" UINT64 ExpectedPC;
extern "C" UINT64 ExpectedR8;
extern "C" UINT64 ExpectedR9;
extern "C" UINT64 ExpectedR10;
extern "C" UINT64 ExpectedR11;
extern "C" UINT64 ExpectedR12;
extern "C" UINT64 ExpectedR13;
extern "C" UINT64 ExpectedR14;
extern "C" UINT64 ExpectedR15;
extern "C" UINT64 ExpectedRDI;
extern "C" UINT64 ExpectedRSI;
extern "C" UINT64 ExpectedRBP;
extern "C" UINT64 ExpectedRBX;
extern "C" UINT64 ExpectedRDX;
extern "C" UINT64 ExpectedRAX;
extern "C" UINT64 ExpectedRCX;
extern "C" UINT64 ExpectedRSP;
extern "C" UINT64 ExpectedEFLAGS;


// Mask of bits to check in EFLAGS:
//
//  AC, OF, DF, TF, SF, ZF, AF, PF, CF
//
static const UINT64 EFLAGS_MASK = 0x40dd5;

#endif
