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
/// @file xed-immed.h
/// 

#ifndef XED_IMMED_H
# define XED_IMMED_H

#include "xed-types.h"
#include "xed-common-defs.h"
#include "xed-util.h"

XED_DLL_EXPORT xed_int64_t xed_immed_from_bytes(xed_int8_t* bytes, xed_uint_t n);
    /*
      Convert an array of bytes representing a Little Endian byte ordering
      of a number (11 22 33 44 55.. 88), in to a a 64b SIGNED number. That gets
      stored in memory in little endian format of course. 

      Input 11 22 33 44 55 66 77 88, 8
      Output 0x8877665544332211  (stored in memory as (lsb) 11 22 33 44 55 66 77 88 (msb))

      Input f0, 1
      Output 0xffff_ffff_ffff_fff0  (stored in memory as f0 ff ff ff   ff ff ff ff)

      Input f0 00, 2
      Output 0x0000_0000_0000_00F0 (stored in memory a f0 00 00 00  00 00 00 00)

      Input 03, 1
      Output 0x0000_0000_0000_0030 (stored in memory a 30 00 00 00  00 00 00 00)
    */


#endif
