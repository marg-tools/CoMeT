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
#include <sstream>
#include <cstdlib>
#include <cstring>

static unsigned long Fibonacci(unsigned long);

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        std::cerr << "Usage: fibonacci [num]" << std::endl;
        return 1;
    }

    unsigned long num = 1000;
    if (argc == 2)
    {
        std::istringstream is;
        is.str(argv[1]);
        is >> num;
        if (!is)
        {
            std::cerr << "Illegal number '" << argv[1] << "'" << std::endl;
            return 1;
        }
    }

    unsigned long fib = Fibonacci(num);
    std::cout << "Entry number " << num << " in the Fibonacci sequence is " << fib << std::endl;
    return 0;
}


static unsigned long Fibonacci(unsigned long num)
{
    static unsigned long *Cache = 0;
    static unsigned long CacheLen = 0;

    if (num < CacheLen && Cache[num])
        return Cache[num];

    unsigned result = 1;
    if (num > 1)
        result = Fibonacci(num-1) + Fibonacci(num-2);

    if (num >= CacheLen)
    {
        size_t sz = 2*num;
        Cache = static_cast<unsigned long *>(realloc(Cache, sz*sizeof(*Cache)));
        memset(&Cache[CacheLen], 0, (sz - CacheLen)*sizeof(*Cache));
        CacheLen = sz;
    }
    Cache[num] = result;
    return result;
}
