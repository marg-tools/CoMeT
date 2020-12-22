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

#if !defined(XED_CHIP_FEATURES_H)
# define XED_CHIP_FEATURES_H
    
#include "xed-common-hdrs.h"
#include "xed-types.h"
#include "xed-isa-set-enum.h"     /* generated */
#include "xed-chip-enum.h"        /* generated */

#define XED_FEATURE_VECTOR_MAX 4
/// @ingroup ISASET
typedef struct 
{
    xed_uint64_t f[XED_FEATURE_VECTOR_MAX];
} xed_chip_features_t;


/// fill in the contents of p with the vector of chip features.
XED_DLL_EXPORT void
xed_get_chip_features(xed_chip_features_t* p, xed_chip_enum_t chip);

/// present = 1 to turn the feature on. present=0 to remove the feature.
XED_DLL_EXPORT void
xed_modify_chip_features(xed_chip_features_t* p,
                         xed_isa_set_enum_t isa_set,
                         xed_bool_t present);

    
#endif
