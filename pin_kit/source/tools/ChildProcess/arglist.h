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

#ifndef _ARGLIST_H_
#define _ARGLIST_H_

#include <string>
#include <list>

using namespace std;

class ARGUMENTS_LIST
{
  public:
    ARGUMENTS_LIST():m_argv(0) {}
    ARGUMENTS_LIST(int argc, const char* const*argv);
    ~ARGUMENTS_LIST();

    void   Add(const string& arg);
    int    Argc() const;
    char** Argv();
    string String() const;

  private:
    void CleanArray();
    void BuildArray();

    list <string> m_argvStrList;
    char **m_argv;
};

#endif
