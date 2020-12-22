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

#include <iostream>
#include "create_and_exit_thread_utils.h"

using std::cerr;
using std::endl;

int main()
{
    cerr << "Application main reached." << endl;
    return RETVAL_FAILURE_APP_COMPLETED;
}
