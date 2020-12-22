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


#ifndef XED_ENCODE_CHECK_H
# define XED_ENCODE_CHECK_H
#include "xed-common-hdrs.h"
#include "xed-types.h"


/// turn off (or on) argument checking if using the checked encoder interface.
/// values 1, 0
/// @ingroup ENC2
XED_DLL_EXPORT void xed_enc2_set_check_args(xed_bool_t on);

#endif
