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

// This little application is used to test passing arguments in probes.
//

extern Bar(int, int, int, int);
extern Baz(int);


void Foo( int a, int b, int c, int d)
{
    Bar( a, b, c, d );
}

int main()
{
    Foo( 12, 345, 678, 90 );
    Foo( 11, 22, 33, 44 );
    Foo( 99, 88, 77, 66 );
    Baz(666);

    return 0;
    
}
