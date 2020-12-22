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

// This little application is used to test calling application functions with 64bit parameters.
//
#include <stdio.h>


#ifdef TARGET_WINDOWS
#include <windows.h>
typedef  __int64 i64_type;
#endif

extern void Bar();

union  union_64{
    double _doub;
    unsigned char _uint8[8];
    i64_type i64;
} UNION_64;

int main()
{
    union  union_64 param1, param2;

    param1._uint8[0]=0xde;
    param1._uint8[1]=0xad;
    param1._uint8[2]=0xbe;
    param1._uint8[3]=0xef;
    param1._uint8[4]=0xde;
    param1._uint8[5]=0xad;
    param1._uint8[6]=0xbe;
    param1._uint8[7]=0xef;

    param2._uint8[0]=0xde;
    param2._uint8[1]=0xad;
    param2._uint8[2]=0xbe;
    param2._uint8[3]=0xef;
    param2._uint8[4]=0xde;
    param2._uint8[5]=0xad;
    param2._uint8[6]=0xbe;
    param2._uint8[7]=0x7f;

    Bar(param1.i64, param2.i64);

    return 0;
}
