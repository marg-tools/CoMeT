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

#include "arglist.h"
#include <stdlib.h>
#include <string.h>

ARGUMENTS_LIST::ARGUMENTS_LIST(int argc, const char* const*argv)
{
    m_argv = new char*[argc];
    for(int i=0; i<argc; i++)
    {
        m_argvStrList.push_back(argv[i]);
        m_argv[i] = new char[strlen(argv[i]) + 1];
        strcpy(m_argv[i], argv[i]);
    }
}

ARGUMENTS_LIST::~ARGUMENTS_LIST()
{
    CleanArray();
}

void ARGUMENTS_LIST::Add(const string& argsStr)
{
    size_t i=0;
    while (i<argsStr.size())
    {
        while (argsStr[i] == ' ') i++;
        size_t j=i;
        while((argsStr[j] != ' ') && (j < argsStr.size())) j++;
        string arg = argsStr.substr(i, j-i);
        m_argvStrList.push_back(arg);
        i = j;
    }
    CleanArray();
}

int ARGUMENTS_LIST::Argc() const
{
    return m_argvStrList.size();
}

char ** ARGUMENTS_LIST::Argv()
{
    if (!m_argv)
        BuildArray();
    return m_argv;
}

string  ARGUMENTS_LIST::String() const
{
    string fullStr;
    list<string>::const_iterator it = m_argvStrList.begin();
    for (; it != m_argvStrList.end(); ++it)
    {
        fullStr += *it;
        fullStr += " ";
    }
    return fullStr;

}

void ARGUMENTS_LIST::CleanArray()
{
    if (!m_argv) return;
    for(int i=0; i < Argc(); i++) delete [] m_argv[i];
    delete [] m_argv;
    m_argv = 0;
}

void ARGUMENTS_LIST::BuildArray()
{
    if (m_argv) CleanArray();

    m_argv = new char*[Argc()+1];
    list<string>::const_iterator it = m_argvStrList.begin();
    int i=0;
    for (; it != m_argvStrList.end(); ++it, ++i)
    {
        m_argv[i] = new char[it->size()+1];
        strcpy(m_argv[i], it->c_str());
    }
    m_argv[i] = 0;
}
