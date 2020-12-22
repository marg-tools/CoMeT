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

#include <stdio.h>

int ToolControlled()
{
    return 1;
}

int DeleteToolControlled()
{
    return 1;
}

int ReInsertToolControlled()
{
    return 1;
}

int ReActivateToolControlled()
{
    return 1;
}

int main()
{
    int res = 0;
    res += ToolControlled(); // Should stop by the tool
    res += DeleteToolControlled();
    res += ToolControlled(); // Should not be stopped at all
    res += ReInsertToolControlled();
    res += ToolControlled(); // Should stop by the tool
    res += ReActivateToolControlled();
    res += ToolControlled(); // Should stop by PinADX
    return 7 - res;
}
