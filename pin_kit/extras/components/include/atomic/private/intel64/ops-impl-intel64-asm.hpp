/*
 * Copyright 2002-2019 Intel Corporation.
 * 
 * This software and the related documents are Intel copyrighted materials, and your
 * use of them is governed by the express license under which they were provided to
 * you ("License"). Unless the License provides otherwise, you may not use, modify,
 * copy, publish, distribute, disclose or transmit this software or the related
 * documents without Intel's prior written permission.
 * 
 * This software and the related documents are provided as is, with no express or
 * implied warranties, other than those that are expressly stated in the License.
 */

// <COMPONENT>: atomic
// <FILE-TYPE>: component private header

#ifndef ATOMIC_PRIVATE_INTEL64_OPS_IMPL_INTEL64_ASM_HPP
#define ATOMIC_PRIVATE_INTEL64_OPS_IMPL_INTEL64_ASM_HPP


extern "C" void ATOMIC_CompareAndSwap8(volatile void *location, const void *oldVal, void *newVal);
extern "C" void ATOMIC_CompareAndSwap16(volatile void *location, const void *oldVal, void *newVal);
extern "C" void ATOMIC_CompareAndSwap32(volatile void *location, const void *oldVal, void *newVal);
extern "C" void ATOMIC_CompareAndSwap64(volatile void *location, const void *oldVal, void *newVal);
extern "C" void ATOMIC_Swap8(volatile void *location, void *oldVal, const void *newVal);
extern "C" void ATOMIC_Swap16(volatile void *location, void *oldVal, const void *newVal);
extern "C" void ATOMIC_Swap32(volatile void *location, void *oldVal, const void *newVal);
extern "C" void ATOMIC_Swap64(volatile void *location, void *oldVal, const void *newVal);
extern "C" void ATOMIC_Increment8(volatile void *location, const void *inc, void *oldVal);
extern "C" void ATOMIC_Increment16(volatile void *location, const void *inc, void *oldVal);
extern "C" void ATOMIC_Increment32(volatile void *location, const void *inc, void *oldVal);
extern "C" void ATOMIC_Increment64(volatile void *location, const void *inc, void *oldVal);

#endif // file guard
