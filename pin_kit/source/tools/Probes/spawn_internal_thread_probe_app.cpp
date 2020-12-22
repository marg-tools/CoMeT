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
 * A App that waits for pin internal thread
 * creation and then finishes successfuly
 * else finishes with error
 */

#if defined (TARGET_WINDOWS)
#include <windows.h>
#else
#include <unistd.h>
#endif

void MySleep(int count)
{
    #if defined (TARGET_WINDOWS)
        Sleep(count);
    #else
        usleep(count * 1000);
    #endif
}

#if defined (TARGET_WINDOWS)
#define EXPORT_SYM extern "C" __declspec(dllexport)
#else
#define EXPORT_SYM extern "C"
#endif

EXPORT_SYM bool IsInternalThreadCreated()
{
    return false;
}

typedef bool (*FUNPTR)();

int main()
{
    volatile FUNPTR threadCreated = IsInternalThreadCreated;
    int i;
    for (i = 0; i < 10; i++)
    {
        // Pin Internal thread created.
        if (threadCreated())
        {
            // Success.
            return 0;
        }

        MySleep(1000);
    }
    // Pin Internal thread was not created.
    return 1;
}
