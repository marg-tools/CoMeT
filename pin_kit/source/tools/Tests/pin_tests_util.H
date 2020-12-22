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

/*! @file
 * Useful includes and macros for tests.
 */

#ifndef PIN_TESTS_UTIL_H
#define PIN_TESTS_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "pin.H"

using namespace std;

#define TEST(COND, MSG) \
    do { \
        if (!(COND)) {cerr << MSG << endl;  exit(1); } \
    } while(0)

#define PRINT_ME_AND_MY_FATHER() \
    do { \
        cout << "I'm " << PIN_GetTid() << ", my father is " << PIN_GetParentTid() << endl;  \
    } while(0)

#endif // PIN_TESTS_UTIL_H

