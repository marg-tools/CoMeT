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

/*! @file
 */

#include <stdio.h>
#include <stdlib.h>
#include "pin.H"

class MyClass {
public:
    MyClass() 
    {
        m_ptr = (char *)malloc(0x1000);
    }

    ~MyClass()
    {
        free(m_ptr);
    }

    void print()
    {
        printf("My pointer is %p\n", m_ptr);
    }

private:
    char *m_ptr;
};

MyClass myClass;

/* ===================================================================== */

int main(int argc, char * argv[])
{
    // Initialize pin
    PIN_Init(argc, argv);

    myClass.print();

    // Start the program, never returns
    PIN_StartProgram();
    
    return 0;
}

