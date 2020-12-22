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

#ifndef XED_CPUID_REC_H
# define XED_CPUID_REC_H
#include "xed-types.h"
#include "xed-portability.h"
#include "xed-cpuid-bit-enum.h"
#include "xed-isa-set-enum.h"


typedef struct {
    xed_uint32_t leaf;    // cpuid leaf
    xed_uint32_t subleaf; // cpuid subleaf
    xed_uint32_t bit;     // the bit number for the feature
    xed_reg_enum_t reg;   // the register containing the bit (EAX,EBX,ECX,EDX)
} xed_cpuid_rec_t;

#define XED_MAX_CPUID_BITS_PER_ISA_SET (4)

/// Returns the name of the i'th cpuid bit associated with this isa-set.
/// Call this repeatedly, with 0 <= i <
/// XED_MAX_CPUID_BITS_PER_ISA_SET. Give up when i ==
/// XED_MAX_CPUID_BITS_PER_ISA_SET or the return value is
/// XED_CPUID_BIT_INVALID.
XED_DLL_EXPORT
xed_cpuid_bit_enum_t
xed_get_cpuid_bit_for_isa_set(xed_isa_set_enum_t isaset,
                              xed_uint_t i);

/// This provides the details of the CPUID bit specification, if the
/// enumeration value is not sufficient.  Returns 1 on success and fills in
/// the structure pointed to by p. Returns 0 on failure.
XED_DLL_EXPORT
xed_int_t
xed_get_cpuid_rec(xed_cpuid_bit_enum_t cpuid_bit,
                  xed_cpuid_rec_t* p);

#endif

