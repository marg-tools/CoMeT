/*BEGIN_LEGAL 
Copyright 2002-2019 Intel Corporation.

This software and the related documents are Intel copyrighted materials, and your
use of them is governed by the express license under which they were provided to
you ("License"). Unless the License provides otherwise, you may not use, modify,
copy, publish, distribute, disclose or transmit this software or the related
documents without Intel's prior written permission.

This software and the related documents are provided as is, with no express or
implied warranties, other than those that are expressly stated in the License.
END_LEGAL */
/// @file xed-common-defs.h 
/// @brief some pervasive defines



#ifndef XED_COMMON_DEFS_H
# define XED_COMMON_DEFS_H

 // for most things it is 4, but one 64b mov allows 8
#define XED_MAX_DISPLACEMENT_BYTES  8

 // for most things it is max 4, but one 64b mov allows 8.
#define XED_MAX_IMMEDIATE_BYTES  8

#define XED_MAX_INSTRUCTION_BYTES  15


#define XED_BYTE_MASK(x) ((x) & 0xFF)
#define XED_BYTE_CAST(x) (XED_STATIC_CAST(xed_uint8_t,x))

#endif









