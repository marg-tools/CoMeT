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
#include <fstream>

int wmain(int argc, wchar_t * argv[])
{
    std::ofstream file;
    file.open("win_unicode.out");
    //internationalization in Japanese (encoded in UTF-16)
    wchar_t internationalization[] = {0x56fd, 0x969B, 0x5316, 0x0000};

    if(argc == 1)
    {
        file << "not equal" << endl;
    } else 
    {
        if(_wcsicmp(argv[1], internationalization) == 0)
        {
            file << "equal" << endl;
        }
        else
        {
            file << "not equal" << endl;
        }
    }
    file.close();
    return 0;
}



