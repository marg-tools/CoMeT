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
#ifndef XED_PATCH_H
# define XED_PATCH_H
#include "xed-encoder-hl.h"

/// @name Patching decoded instructions
//@{


/// Replace a memory displacement.
/// The widths of original displacement and replacement must match.
/// @param xedd A decoded instruction.
/// @param itext The corresponding encoder output, byte array.
/// @param disp  A xed_enc_displacement_t object describing the new displacement.
/// @returns xed_bool_t  1=success, 0=failure
/// @ingroup ENCHLPATCH
XED_DLL_EXPORT xed_bool_t
xed_patch_disp(xed_decoded_inst_t* xedd,
               xed_uint8_t* itext,
               xed_enc_displacement_t disp);

/// Replace a branch displacement.
/// The widths of original displacement and replacement must match.
/// @param xedd A decoded instruction.
/// @param itext The corresponding encoder output, byte array.
/// @param disp  A xed_encoder_operand_t object describing the new displacement.
/// @returns xed_bool_t  1=success, 0=failure
/// @ingroup ENCHLPATCH
XED_DLL_EXPORT xed_bool_t
xed_patch_relbr(xed_decoded_inst_t* xedd,
                xed_uint8_t* itext,
                xed_encoder_operand_t disp);

/// Replace an imm0 immediate value.
/// The widths of original immediate and replacement must match.
/// @param xedd A decoded instruction.
/// @param itext The corresponding encoder output, byte array.
/// @param imm0  A xed_encoder_operand_t object describing the new immediate.
/// @returns xed_bool_t  1=success, 0=failure
/// @ingroup ENCHLPATCH
XED_DLL_EXPORT xed_bool_t
xed_patch_imm0(xed_decoded_inst_t* xedd,
               xed_uint8_t* itext,
               xed_encoder_operand_t imm0);

//@}
#endif
