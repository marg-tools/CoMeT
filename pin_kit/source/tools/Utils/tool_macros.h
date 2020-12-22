/*
 * Copyright 2002-2019 Intel Corporation.
 * 
 * This software is provided to you as Sample Source Code as defined in the accompanying
 * End User License Agreement for the Intel(R) Software Development Products ("Agreement")
 * section 1.L.
 * 
 * This software and the related documents are provided as is, with no express or implied
 * warranties, other than those that are expressly stated in the License.
 */

/*
 * Auxiliary macros for tools/apps located in PinTools
 *
 * XXX - Consider renaming filename to utils_macros.h
 */

#ifndef __TOOL_MACROS_H__
#define __TOOL_MACROS_H__

/*
 * C_MANGLE(name) - Mangle a C function name to its corresponding assembler function name
 */
#ifdef TARGET_MAC
# define C_MANGLE(name) "_" name
# define SHARED_LIB(name) name ".dylib"
#else
# define C_MANGLE(name) name
# if defined(TARGET_LINUX)
#  define SHARED_LIB(name) name ".so"
# elif defined(TARGET_WINDOWS)
#  define SHARED_LIB(name) name ".dll"
# endif
#endif

// macOS adds '_' prefix to function names (as well as to calls to functions).
// We have assembly files which are shared by OS's. Therefore functions names should be the same across all OS's.
// In order to force assembly function to be recognized by there original names without the prefix,
// we must use the below macro in order to declare them as assembly functions which force the compiler
// not to add the prefix when calling assembly function from a C/CXX function.
#ifdef TARGET_WINDOWS
#define ASMNAME(name)
#else
#define ASMNAME(name) asm(name)
#endif

#endif // __TOOL_MACROS_H__

