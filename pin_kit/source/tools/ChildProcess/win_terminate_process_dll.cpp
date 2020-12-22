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

#define _WIN32_WINNT   0x0400 
#include <Windows.h>
#include <iostream>
#include <stdio.h>
using std::string;
using std::cerr;
using std::endl;
using std::cout;
using std::flush;
static volatile int i = 0;

//Verify that the LFH is available. return true when running under debugger.
bool VerifyLFHAvailable()
{
    if(IsDebuggerPresent())
    {
        //LFH is not available unser debugger
        return true;
    }
    else
    {
        ULONG heapInfo = 2;
        return HeapSetInformation(GetProcessHeap(), HeapCompatibilityInformation, &heapInfo, sizeof(ULONG));
    }
}

BOOL WINAPI DllMain(HANDLE hDll, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason) 
    {
      case DLL_PROCESS_ATTACH:
      {
		  if(VerifyLFHAvailable())
		  {		  
              cout << "Terminating process in DllMain(PROCESS_ATTACH)" << endl << flush;
		  }
		  else
		  {
              cout << "ERROR: LFH is not available" << endl << flush;
		  }
          TerminateProcess(GetCurrentProcess(), 0);
          i = 12;
          return FALSE;
          break;
      }  
      case DLL_THREAD_ATTACH:
          break;
      case DLL_THREAD_DETACH: 
          break;
      case DLL_PROCESS_DETACH:
          break;
      default:
          break; 
    } 
    return TRUE; 
}

extern "C" __declspec(dllexport) int Something() {return i;}
