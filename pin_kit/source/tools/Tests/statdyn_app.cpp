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

/* Description:
 * This executable creates two symbols: statdyn_app_staticFunction and statdyn_app_dynamicFunction.
 * The test tool then checks that statdyn_app_staticFunction is a static symbol (defined only in
 * the SYMTAB table) and that statdyn_app_dynamicFunction is a dynamic symbol (defined in the
 * DYNSYM table).
 * The main program itself actually does nothing, we only need to create the two symbols for the
 * tool. The call to statdyn_app_staticFunction is there to prevent an error during compilation due
 * to a static function which is not used.
 */

static bool statdyn_app_staticFunction()
{
    return true;
}

bool statdyn_app_dynamicFunction()
{
    return true;
}

int main()
{
    statdyn_app_staticFunction();
    return 0;
}
