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
 *  pin tool combined from multi-DLLs (main_dll, dynamic_secondary_dll, static_secondary_dll). 
 */

#include <iostream>
#include <fstream>

using std::ofstream;
using std::hex;
using std::endl;
using std::showbase;

ofstream outfile;

extern "C" __declspec( dllexport ) void Init1(const char* out_filename)
{
    outfile.open(out_filename);
    outfile << hex << showbase;
}

extern "C" __declspec( dllexport ) void BeforeBBL1(void * ip)
{
    outfile << "Before BBL, ip " << ip << endl;
}

extern "C" __declspec( dllexport ) void Fini1()
{
    outfile.close();
}

// Define main - will never be called
// can be avoided by removing /EXPORT:main from link flags
int main(int argc, char * argv[])
{
    return 0;
}
