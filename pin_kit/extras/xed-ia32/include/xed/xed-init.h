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
/// @file xed-init.h 
/// 




#if !defined(XED_INIT_H)
# define XED_INIT_H


/// @ingroup INIT
///   This is the call to initialize the XED encode and decode tables. It
///   must be called once before using XED.
void XED_DLL_EXPORT  xed_tables_init(void);

////////////////////////////////////////////////////////////////////////////

#endif
