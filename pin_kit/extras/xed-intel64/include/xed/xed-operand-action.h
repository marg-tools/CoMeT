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
/// @file xed-operand-action.h
/// 

#if !defined(XED_OPERAND_ACTION_H)
# define XED_OPERAND_ACTION_H

#include "xed-types.h"
#include "xed-operand-action-enum.h"

XED_DLL_EXPORT xed_uint_t xed_operand_action_read(const xed_operand_action_enum_t rw);
XED_DLL_EXPORT xed_uint_t xed_operand_action_read_only(const xed_operand_action_enum_t rw);
XED_DLL_EXPORT xed_uint_t xed_operand_action_written(const xed_operand_action_enum_t rw);
XED_DLL_EXPORT xed_uint_t xed_operand_action_written_only(const xed_operand_action_enum_t rw);
XED_DLL_EXPORT xed_uint_t xed_operand_action_read_and_written(const xed_operand_action_enum_t rw);
XED_DLL_EXPORT xed_uint_t xed_operand_action_conditional_read(const xed_operand_action_enum_t rw);
XED_DLL_EXPORT xed_uint_t xed_operand_action_conditional_write(const xed_operand_action_enum_t rw);

#endif

