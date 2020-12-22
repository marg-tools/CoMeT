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

//  this application fails so we can check errno.

#include <stdio.h>

#if defined (TARGET_WINDOWS)
#include <windows.h>
#define EXPORT_SYM __declspec( dllexport ) 
#else
#include <errno.h>
#define EXPORT_SYM extern
#endif

EXPORT_SYM void CheckError();

int main(int argc, char *argv[])
{
   FILE *f = fopen("non-existent-file", "r");

   if ( !f )
   {
       CheckError();
       fprintf(stdout, "App: cannot open non-existent file\n");
       return 0; 
   }
}
