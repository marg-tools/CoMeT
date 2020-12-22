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
 * 
 * This file incorporates work covered by the following copyright and permission notice:
 */

/*  $OpenBSD: setjmp.h,v 1.2 2000/08/05 22:07:32 niklas Exp $   */
/*  $NetBSD: setjmp.h,v 1.1 1994/12/20 10:36:43 cgd Exp $   */

/*
 * machine/setjmp.h: machine dependent setjmp-related information.
 */

#ifdef TARGET_WINDOWS

#define _JBLEN  6      /* size, in void*s, of a jmp_buf */

#else

#define _JBLEN  7      /* size, in void*s, of a jmp_buf */

#endif
