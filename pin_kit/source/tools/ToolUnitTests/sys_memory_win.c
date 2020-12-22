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


/*! @file
 *  Implementation of the memory management API in Windows. 
 */
#include "sys_memory.h"
#include <windows.h>

/*!
 *  Given a MEM_PROTECTION attribute, return corresponding Windows protection flag. 
 */
static DWORD SysProtection(MEM_PROTECTION protect)
{
    switch (protect)
    {
        case MEM_READ_EXEC:
            return PAGE_EXECUTE_READ;
        case MEM_READ_WRITE_EXEC:
            return PAGE_EXECUTE_READWRITE;
        default:
            return PAGE_NOACCESS;
    }
}

/*!
 *  Implementation of the memory management API. 
 */
size_t GetPageSize()
{
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    return (size_t)(sysInfo.dwPageSize);
}

void * MemAlloc(size_t size, MEM_PROTECTION protect)
{
    return VirtualAlloc(0, size, MEM_COMMIT, SysProtection(protect));
}

void MemFree(void * addr, size_t size)
{
    VirtualFree(addr, 0, MEM_RELEASE);
}

BOOL MemProtect(void * addr, size_t size, MEM_PROTECTION protect)
{
    DWORD oldProtect;
    return VirtualProtect(addr, size, SysProtection(protect), &oldProtect);
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
