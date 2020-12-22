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
#include <cstring>
using std::endl;

int main(int argc, char * argv[])
{
    std::ofstream file;
    file.open("unix_unicode.out");
    //internationalization in Japanese (encoded in UTF-8)
    char i18n[] = {(char)0xE5, (char)0x9B, (char)0xBD, (char)0xE9, (char)0x9A, (char)0x9B, (char)0xE5, (char)0x8C, (char)0x96, (char)0x00};
    if(argc == 1)
    {
        file << "not equal" << endl;
    } else 
    {
        if(strcmp(argv[1], i18n) == 0)
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

