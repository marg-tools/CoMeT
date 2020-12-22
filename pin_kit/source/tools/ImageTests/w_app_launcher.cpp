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

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <Windows.h>
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;
using std::cerr;

// launch given application, write application's PID to stdout

int main(int argc, char * argv[], char * envp[])
{
    string cmdLine = "";
    // Build command line
    for(int i = 1; i < argc; i++)
    {
        cmdLine += string(argv[i]);
        if(i != argc - 1)
        {
            cmdLine +=  string(" ");
        }
    }
    
    // Invoke Application
    STARTUPINFO         si;
    PROCESS_INFORMATION  pi;
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(STARTUPINFO);
    memset(&pi, 0, sizeof(pi));
    if (!CreateProcess(NULL, (LPSTR)cmdLine.c_str(), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        cout <<  "0" << endl;
        cerr <<  "Failed to create " << cmdLine << endl;
        exit(-1);
    }
    
    char digitBuffer[64];
    cout << itoa(pi.dwProcessId, digitBuffer, 10);    
    return 0;
}

