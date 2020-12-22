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

#include <windows.h>
#include <iostream>

typedef void (*FOOPTR)();


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Must specify pathname of library to load.\n";
        return 1;
    }

    HMODULE mod = LoadLibraryA(argv[1]);
    if (!mod)
    {
        std::cerr << "Unable to load library '" << argv[1] << "\n";
        return 1;
    }

    FOOPTR foo = reinterpret_cast<FOOPTR>(GetProcAddress(mod, "Foo"));
    if (!foo)
    {
        std::cerr << "Unable to find function Foo\n";
        return 1;
    }
    foo();

    FreeLibrary(mod);
    return 0;
}
