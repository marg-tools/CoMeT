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
/// @file xed-isa-set.h


#if !defined(XED_ISA_SET_H)
# define XED_ISA_SET_H
    
#include "xed-common-hdrs.h"
#include "xed-types.h"
#include "xed-isa-set-enum.h"     /* generated */
#include "xed-chip-enum.h"        /* generated */

/// @ingroup ISASET
/// return 1 if the isa_set is part included in the specified chip, 0
///  otherwise.
XED_DLL_EXPORT xed_bool_t
xed_isa_set_is_valid_for_chip(xed_isa_set_enum_t isa_set,
                              xed_chip_enum_t chip);

    
#endif
