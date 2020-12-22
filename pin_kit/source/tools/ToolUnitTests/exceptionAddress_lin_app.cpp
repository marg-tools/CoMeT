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

using std::cerr;
using std::endl;

static void pinException() {
    cerr << "APP: in pinException" << endl;
}

static void toolException() {
    cerr << "APP: in toolException" << endl;
}

static int appException() {
    cerr << "APP: in appException" << endl;
    int zero = 0; // This is to avoid getting a compiler warning of division by zero.
    return 1 / zero;
}

int main() {
    
    // Cause a Pin exception via PIN_SafeCopyEx.
    pinException();
    
    // Cause a tool exception.
    toolException();
    
    // Cause an application exception (SIGFPE) - divide by zero.
    appException();
    
    return 0;
}
