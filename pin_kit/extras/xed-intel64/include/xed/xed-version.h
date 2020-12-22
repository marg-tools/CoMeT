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

#if !defined(XED_VERSION_H)
# define XED_VERSION_H
#include "xed-common-hdrs.h"

///@ingroup INIT
/// Returns a string representing XED svn commit revision and time stamp.
XED_DLL_EXPORT char const* xed_get_version(void);
///@ingroup INIT
/// Returns a copyright string.
XED_DLL_EXPORT char const* xed_get_copyright(void);
#endif
