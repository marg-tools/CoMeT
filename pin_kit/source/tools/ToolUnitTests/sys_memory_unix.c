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
 *  Implementation of the memory management API in Unix. 
 */
#include "sys_memory.h"
#include <unistd.h>
#include <sys/mman.h>

/*!
 *  Given a MEM_PROTECTION attribute, return corresponding Unix protection flags. 
 */
static int SysProtection(MEM_PROTECTION protect)
{
    switch (protect)
    {
    case MEM_READ_EXEC:
        return PROT_READ|PROT_EXEC;
    case MEM_READ_WRITE_EXEC:
        return PROT_READ|PROT_WRITE|PROT_EXEC;
    default:
        return PROT_NONE;
    }
}

/*!
 *  Implementation of the memory management API. 
 */
size_t GetPageSize()
{
    return (size_t)getpagesize();
}

void MemFree(void * addr, size_t size)
{
    munmap(addr, size);
}

BOOL MemProtect(void * addr, size_t size, MEM_PROTECTION protect)
{
    
    return (-1 != mprotect(addr, size, SysProtection(protect)));
}

void * MemAlloc(size_t size, MEM_PROTECTION protect)
{
#if defined(TARGET_MAC) || defined(TARGET_BSD)
    void * addr = mmap(0, size, SysProtection(protect), MAP_ANON | MAP_PRIVATE, -1, 0);
#else
    void * addr = mmap(0, size, SysProtection(protect), MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
#endif
    if (addr != MAP_FAILED)
    {
        return addr;
    }
    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
