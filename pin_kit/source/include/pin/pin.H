/*
 * Copyright 2002-2019 Intel Corporation.
 * 
 * This software and the related documents are Intel copyrighted materials, and your
 * use of them is governed by the express license under which they were provided to
 * you ("License"). Unless the License provides otherwise, you may not use, modify,
 * copy, publish, distribute, disclose or transmit this software or the related
 * documents without Intel's prior written permission.
 * 
 * This software and the related documents are provided as is, with no express or
 * implied warranties, other than those that are expressly stated in the License.
 */

// Multiple inclusion is an error in pin sources, but ok for pintool
// writers
#if !defined(PIN_H)

#define PIN_H
extern "C"{
#include "xed-interface.h"
}
#include "pin_version.h"
#include "level_base.PLH"
#include "level_core.PLH"
#include "level_vmapi.PLH"
#include "level_pinclient.PLH"

#define DisableKnobFamily UNSUPPORTED
#define EnableKnobFamily UNSUPPORTED

using namespace LEVEL_PINCLIENT;

#endif

