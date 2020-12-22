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

#include "context_utils.h"


/////////////////////
// API FUNCTIONS IMPLEMENTATION
/////////////////////

void StoreContext(const CONTEXT * ctxt)
{
    vector<REG> regs = GetTestRegs();
    int numOfRegs = regs.size();
    for (int r = 0; r < numOfRegs; ++r)
    {
        REG reg = regs[r];
        PIN_GetContextRegval(ctxt, reg, GetRegval(reg));
    }
}

void ModifyContext(CONTEXT * ctxt)
{
    vector<REG> regs = GetTestRegs();
    int numOfRegs = regs.size();
    for (int r = 0; r < numOfRegs; ++r)
    {
        REG reg = regs[r];
        PIN_SetContextRegval(ctxt, reg, GetToolRegisterValue(reg));
    }
}
