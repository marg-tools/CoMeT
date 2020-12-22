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
/// @file xed-common-hdrs.h
/// 



#ifndef XED_COMMON_HDRS_H
# define XED_COMMON_HDRS_H



#if defined(__FreeBSD__) || defined(__NetBSD__)
# define XED_BSD
#endif
#if defined(__linux__)
# define XED_LINUX
#endif
#if defined(_MSC_VER)
# define XED_WINDOWS
#endif
#if defined(__APPLE__)
# define XED_MAC
#endif


#if defined(XED_DLL)
//  __declspec(dllexport) works with GNU GCC or MS compilers, but not ICC
//  on linux

#  if defined(XED_WINDOWS)
#     define XED_DLL_EXPORT __declspec(dllexport)
#     define XED_DLL_IMPORT __declspec(dllimport)
#  elif defined(XED_LINUX)  || defined(XED_BSD) || defined(XED_MAC)
#     define XED_DLL_EXPORT __attribute__((visibility("default")))
#     define XED_DLL_IMPORT
#  else
#     define XED_DLL_EXPORT
#     define XED_DLL_IMPORT
#  endif
    
#  if defined(XED_BUILD)
    /* when building XED, we export symbols */
#    define XED_DLL_GLOBAL XED_DLL_EXPORT
#  else
    /* when building XED clients, we import symbols */
#    define XED_DLL_GLOBAL XED_DLL_IMPORT
#  endif
#else
# define XED_DLL_EXPORT 
# define XED_DLL_IMPORT
# define XED_DLL_GLOBAL
#endif
    
#endif

