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

#ifndef _SYS_MMAN_H_
#define _SYS_MMAN_H_

#ifdef TARGET_MAC
#include <sys/mac/mman.h>
#else
#include <sys/nonmac/mman.h>
#endif


#endif /* _SYS_MMAN_H_ */
