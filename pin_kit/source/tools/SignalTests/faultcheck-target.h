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

#ifndef FAULT_CHECK_TARGET_H
#define FAULT_CHECK_TARGET_H

#include <signal.h>
#include "raise-exception-addrs.h"

typedef enum
{
    TSTATUS_NOFAULT,    /* test did not raise fault */
    TSTATUS_SKIP,       /* skip this test */
    TSTATUS_DONE        /* there are no more tests */
} TSTATUS;

extern TSTATUS DoTest(unsigned int);
extern void PrintSignalContext(int, const siginfo_t *, void *);
extern void SetLabelsForPinTool(const RAISE_EXCEPTION_ADDRS *);

#endif
