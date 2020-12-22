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

#if defined(TARGET_WINDOWS)
# include <Windows.h>
# define EXPORT_SYM __declspec( dllexport )
#else
# define EXPORT_SYM
#endif

// Empty function - this is simply a placeholder for the tool to start printing register values.
extern "C" EXPORT_SYM void Start()
{
    // do nothing
}

// Empty function - this is simply a placeholder for the tool to stop printing register values.
extern "C" EXPORT_SYM void Stop()
{
    // do nothing
}

// Do some calculations and let the tool print the registers.
long double Work()
{
    int inta = 1;
    int intb = 2;
    int intc = inta - intb;
    int intd = intb - inta;
    int inte = intc * intd;

    long double lda = 1234.5678;
    long double ldb = 8765.4321;
    long double ldc = lda / ldb;
    long double ldd = ldb / lda;
    long double lde = ldc + ldd;
    return (lde * (long double)inte);
}

int main()
{
    Start();
    Work();
    Stop();
}
