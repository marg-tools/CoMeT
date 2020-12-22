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

#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using std::string;

extern "C" void TellPinSectionCount(int sectionCount)
{
    // Pin tool can place instrumentation here to learn sections count.
}

int GetSectionCount(string command)
{
    string result, file, word;
    FILE* output(popen(command.c_str(), "r"));
    char buffer[256];
    std::vector<string> vec;

    while(fgets(buffer, sizeof(buffer), output) != NULL)
    {
        file = buffer;
        result += file.substr(0, file.size() - 1);
    }

    std::istringstream iss(result);
    while (iss >> word)
    {
        vec.push_back(word);
    }

    pclose(output);

    return atoi(vec.back().c_str());
}

int main(int argc, char** argv)
{
    int sectionCount = 0;
    string imgName(argv[0]);

    sectionCount = GetSectionCount("readelf -h " + imgName + " | grep 'Number of section headers'");

    TellPinSectionCount(sectionCount);

    return 0;
}
