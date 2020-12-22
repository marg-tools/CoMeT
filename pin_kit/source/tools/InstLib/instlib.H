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

#ifndef INSTLIB_H
#define INSTLIB_H

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

#define ISIMPOINT_MAX_THREADS 160

#include "filter.H"
#include "skipper.H"
#include "icount.H"
#include "follow_child.H"

extern "C"{
#include "xed-interface.h"
}

#endif
