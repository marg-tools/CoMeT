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

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <stdint.h>
using std::string;
using std::hex;
using std::ifstream;
using std::cerr;
using std::endl;
using std::cout;


int main()
{
    string line;
    ifstream maps("/proc/self/maps");
    const string vvar = "[vvar]";

    while (std::getline(maps, line))
    {
        size_t idx = line.find(vvar);
        if (string::npos != idx && line.substr(idx) == vvar)
        {
            idx = line.find("-");
            if (string::npos == idx)
            {
                cerr << "Failed to parse line '" << line << "'" << endl;
                return 1;
            }
            intptr_t vvarStart = strtoul(line.substr(0, idx).c_str(), NULL, 0x10);
            cout << hex << "0x" << vvarStart << ":0x" << (vvarStart + getpagesize()) << endl;
            return 0;
        }
    }
    return 0;
}
