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

#if !defined(XED_GET_TIME_H)
#   define XED_GET_TIME_H

#   include "xed-portability.h"
#   include "xed-types.h"
#   if defined(__INTEL_COMPILER) && __INTEL_COMPILER > 810  && !defined(_M_IA64)
#      include <ia32intrin.h>
#   endif
#   if defined(__INTEL_COMPILER) && __INTEL_COMPILER >= 810  && !defined(_M_IA64)
#      if __INTEL_COMPILER < 1000
#         pragma intrinsic(__rdtsc)
#      endif
#   endif
#   if !defined(__INTEL_COMPILER)
       /* MSVS8 and later */
#      if defined(_MSC_VER) && _MSC_VER >= 1400 && !defined(_M_IA64)
#         include <intrin.h>
#         pragma intrinsic(__rdtsc)
#      endif
#      if defined(__GNUC__)
#         include <x86intrin.h>
#      endif
#   endif


static XED_INLINE  xed_uint64_t xed_get_time(void) {
    xed_union64_t ticks;
#   if defined(__GNUC__) 
#      if defined(__i386__) || defined(i386) || defined(i686) || defined(__x86_64__)
#         if __GNUC__ >= 5 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9 && __GNUC_PATCHLEVEL__ >= 3)
               ticks.u64 = __rdtsc();
#         else            
               __asm__ volatile ("rdtsc":"=a" (ticks.s.lo32), "=d"(ticks.s.hi32));
#         endif               
#         define XED_FOUND_RDTSC
#      endif
#   endif
#   if defined(__INTEL_COMPILER) &&  __INTEL_COMPILER>=810 && !defined(_M_IA64)
       ticks.u64 = __rdtsc();
#      define XED_FOUND_RDTSC
#   endif
#   if !defined(__INTEL_COMPILER)
#      if !defined(XED_FOUND_RDTSC) && defined(_MSC_VER) && _MSC_VER >= 1400 && \
                         !defined(_M_IA64) && !defined(_MANAGED)    /* MSVS7, 8 */
          ticks.u64 = __rdtsc();
#         define XED_FOUND_RDTSC
#      endif
#   endif
#   if !defined(XED_FOUND_RDTSC)
       ticks.u64 = 0;
#   endif
    return ticks.u64;
}
#undef XED_FOUND_RDTSC
#endif
