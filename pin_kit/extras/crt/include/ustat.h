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

#ifndef _PINCRT_USTAT_
#define _PINCRT_USTAT_

#include <sys/types.h>

struct ustat
{
    daddr_t f_tfree;      /* Total free blocks */
    ino_t   f_tinode;     /* Number of free inodes */
    char    f_fname[6];   /* Filsys name */
    char    f_fpack[6];   /* Filsys pack name */
};

#endif // _PINCRT_USTAT_
