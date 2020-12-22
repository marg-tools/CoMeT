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

#ifndef CONTEXT_UTILS_H
#define CONTEXT_UTILS_H

#include "regvalue_test_utils.h"

void StoreContext(const CONTEXT * ctxt);
void ModifyContext(CONTEXT * ctxt);

#endif // CONTEXT_UTILS_H
