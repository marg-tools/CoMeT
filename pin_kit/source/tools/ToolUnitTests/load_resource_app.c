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

#include <windows.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    // Modify field in TEB that is temporary used by OS loader to point at image name
    // when binary image is mapped for execution.
    WCHAR *str = L"garbage";
    struct _TEB *pt = NtCurrentTeb();
    PVOID *aup = &((PNT_TIB)pt)->ArbitraryUserPointer;
    *aup = (PVOID)str;

    {
        // LOAD_LIBRARY_AS_IMAGE_RESOURCE flag orders to map DLL as image but not for execution.
        // OS loader doesn't temporary modify ArbitraryUserPointer TEB field in this case,
        // so value set by the application remains visible.
        HMODULE hMod = LoadLibraryEx("mswsock.dll", NULL, LOAD_LIBRARY_AS_IMAGE_RESOURCE);
        DWORD err = GetLastError();
        printf("base = %x, error = %x\n", hMod, err);
        return (hMod == 0);
    }
}
