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
#if !defined(XED_BUILD_DEFINES_H)
#  define XED_BUILD_DEFINES_H

#  if !defined(XED_AMD_ENABLED)
#    define XED_AMD_ENABLED
#  endif
#  if !defined(XED_AVX)
#    define XED_AVX
#  endif
#  if !defined(XED_CET)
#    define XED_CET
#  endif
#  if !defined(XED_DECODER)
#    define XED_DECODER
#  endif
#  if !defined(XED_DLL)
#    define XED_DLL
#  endif
#  if !defined(XED_ENCODER)
#    define XED_ENCODER
#  endif
#  if !defined(XED_GIT_VERSION)
#    define XED_GIT_VERSION "11.0.1"
#  endif
#  if !defined(XED_MPX)
#    define XED_MPX
#  endif
#  if !defined(XED_SUPPORTS_AVX512)
#    define XED_SUPPORTS_AVX512
#  endif
#  if !defined(XED_SUPPORTS_LZCNT_TZCNT)
#    define XED_SUPPORTS_LZCNT_TZCNT
#  endif
#  if !defined(XED_SUPPORTS_SHA)
#    define XED_SUPPORTS_SHA
#  endif
#  if !defined(XED_SUPPORTS_WBNOINVD)
#    define XED_SUPPORTS_WBNOINVD
#  endif
#  if !defined(XED_VIA_ENABLED)
#    define XED_VIA_ENABLED
#  endif
#endif
