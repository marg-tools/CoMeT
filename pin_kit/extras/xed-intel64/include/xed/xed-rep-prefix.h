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

#ifndef XED_REP_PREFIX_H
# define XED_REP_PREFIX_H

#include "xed-types.h"
#include "xed-common-defs.h"
#include "xed-iclass-enum.h"
/// @name REP-like prefix removal and addition
//@{

/// @ingroup DEC Take an instruction with a REP/REPE/REPNE prefix and
/// return the corresponding xed_iclass_enum_t without that prefix. The
/// return value differs from the other functions in this group: If the
/// input iclass does not have REP/REPNE/REPE prefix, the function returns
/// the original instruction.
XED_DLL_EXPORT xed_iclass_enum_t xed_rep_remove(xed_iclass_enum_t x);

/// @ingroup DEC Take an #xed_iclass_enum_t value without a REPE prefix and
/// return the corresponding #xed_iclass_enum_t with a REPE prefix. If the
/// input instruction cannot have have a REPE prefix, this function returns
/// XED_ICLASS_INVALID.
XED_DLL_EXPORT xed_iclass_enum_t xed_repe_map(xed_iclass_enum_t iclass);

/// @ingroup DEC Take an #xed_iclass_enum_t value without a REPNE prefix
/// and return the corresponding #xed_iclass_enum_t with a REPNE prefix. If
/// the input instruction cannot have a REPNE prefix, this function returns
/// XED_ICLASS_INVALID.
XED_DLL_EXPORT xed_iclass_enum_t xed_repne_map(xed_iclass_enum_t iclass);

/// @ingroup DEC Take an #xed_iclass_enum_t value without a REP prefix and
/// return the corresponding #xed_iclass_enum_t with a REP prefix. If the
/// input instruction cannot have a REP prefix, this function returns
/// XED_ICLASS_INVALID.
XED_DLL_EXPORT xed_iclass_enum_t xed_rep_map(xed_iclass_enum_t iclass);

/// @ingroup DEC Take an #xed_iclass_enum_t value for an instruction with a
/// REP/REPNE/REPE prefix and return the corresponding #xed_iclass_enum_t
/// without that prefix. If the input instruction does not have a
/// REP/REPNE/REPE prefix, this function returns XED_ICLASS_INVALID.
XED_DLL_EXPORT xed_iclass_enum_t xed_norep_map(xed_iclass_enum_t iclass);
//@}
#endif
