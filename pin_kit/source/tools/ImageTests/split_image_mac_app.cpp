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

/**
 * This application prints all the text and data segments of every image 
 * loaded using the dyld interfaces.
 * For more details on the test see the comment in split_image.cpp
 */
#include <cstdio>
#include <cstdlib>
#include <mach-o/dyld.h>
#include <mach-o/getsect.h>

#if defined(TARGET_IA32)
# define SPLIT_IMAGE_MACH_HEADER const struct mach_header
#else
# define SPLIT_IMAGE_MACH_HEADER const struct mach_header_64
#endif

int main()
{
    for (int i=0; i < _dyld_image_count(); ++i)
    {
        unsigned long data_len, text_len;
        void *data_seg = getsegmentdata((SPLIT_IMAGE_MACH_HEADER *)_dyld_get_image_header(i), "__DATA", &data_len);
        void *text_seg = getsegmentdata((SPLIT_IMAGE_MACH_HEADER *)_dyld_get_image_header(i), "__TEXT", &text_len);
        if (data_seg) 
            fprintf(stderr, "%s, %p-%p\n", _dyld_get_image_name(i), data_seg, ((char*)data_seg) + data_len - 1);
        if (text_seg)
            fprintf(stderr, "%s, %p-%p\n", _dyld_get_image_name(i), text_seg, ((char*)text_seg) + text_len - 1);
    }
    return 0;
}
