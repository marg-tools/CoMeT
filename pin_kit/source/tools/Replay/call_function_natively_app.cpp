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

#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

#if defined(TARGET_WINDOWS)
# define EXPORT_SYM __declspec( dllexport )
#else
# define EXPORT_SYM
#endif


extern "C" EXPORT_SYM const char* world()
{
    return "world";
}

extern "C" EXPORT_SYM const char* helloX(char* buf)
{
    strcpy(buf, "hello ");
    strcat(buf, world());
    return buf;
}

extern "C" EXPORT_SYM int main()
{
    char buf[128];
    cout << helloX(buf) << endl;
    return 0;
}
