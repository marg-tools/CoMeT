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
/*
/// @file xed-interface.h 
/// 
*/



#if !defined(XED_INTERFACE_H)
# define XED_INTERFACE_H

#if defined(_WIN32) && defined(_MANAGED)
#pragma unmanaged
#endif
    
#include "xed-build-defines.h" /* generated */
#include "xed-portability.h"
    
#include "xed-common-hdrs.h"
#include "xed-types.h"
#include "xed-operand-enum.h"

#include "xed-init.h"
#include "xed-decode.h"
#include "xed-ild.h"

#include "xed-state.h" /* dstate, legacy */
#include "xed-syntax-enum.h"
#include "xed-reg-class-enum.h" /* generated */
#include "xed-reg-class.h"

#if defined(XED_ENCODER)
# include "xed-encode.h"
# include "xed-encoder-hl.h"
# include "xed-patch.h"
#endif
#if defined(XED_ENC2_ENCODER)
# include "xed-encode-direct.h"
# include "xed-encode-check.h"
#endif

#include "xed-util.h"
#include "xed-operand-action.h"

#include "xed-version.h"
#include "xed-decoded-inst.h"
#include "xed-decoded-inst-api.h"
#include "xed-inst.h"
#include "xed-iclass-enum.h"    /* generated */
#include "xed-category-enum.h"  /* generated */
#include "xed-extension-enum.h" /* generated */
#include "xed-attribute-enum.h" /* generated */
#include "xed-exception-enum.h" /* generated */
#include "xed-operand-element-type-enum.h"  /* generated */
#include "xed-operand-element-xtype-enum.h" /* generated */

#include "xed-disas.h"  // callbacks for disassembly
#include "xed-format-options.h" /* options for disassembly  */

#include "xed-iform-enum.h"     /* generated */
/* indicates the first and last index of each iform, for building tables */
#include "xed-iformfl-enum.h"   /* generated */
/* mapping iforms to iclass/category/extension */
#include "xed-iform-map.h"
#include "xed-rep-prefix.h"  


#include "xed-agen.h"
#include "xed-cpuid-rec.h"
#include "xed-isa-set.h"  


#endif
