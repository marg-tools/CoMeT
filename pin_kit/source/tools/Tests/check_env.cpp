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
#include <vector>
#include <algorithm>
#include <string>

void initSkipList(std::vector<std::string>& skipList)
{
    skipList.push_back("PPID");
    skipList.push_back("PIN_");
    skipList.push_back("_=");
    skipList.push_back("SSH_CLIENT");
    skipList.push_back("SSH_CONNECTION");
    skipList.push_back("RANDOM");
    skipList.push_back("MFLAGS");
}

int main(int argc, char **argv, char **envp)
{
    std::vector<std::string> skipList;
    initSkipList(skipList);

    std::vector<std::string> e;

    for (char **currVar = envp; *currVar != NULL; ++currVar)
    {
        bool skipCurrVar = false;
        std::string currStr(*currVar);
        for (std::vector<std::string>::iterator it=skipList.begin(); it != skipList.end(); ++it)
        {
            if (currStr.compare(0, (*it).size(), *it) == 0)
            {
                skipCurrVar = true;
                break;
            }
        }

        if (skipCurrVar) continue;
        e.push_back(currStr);
    }
    // Pin might change the order of the environment variables, so we want to
    // print them sorted, so print order will be the same for the same env.
    // 
    std::sort(e.begin(), e.end());

    for (std::vector<std::string>::iterator it=e.begin(); it != e.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    return 0;
}
