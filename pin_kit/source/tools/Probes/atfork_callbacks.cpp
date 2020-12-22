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
#include "pin.H"
#include "atfork_callbacks.h"
using std::cerr;
using std::endl;

/***********************************************
*
*   This pintool (atfork_callbacks.cpp) also prints numbers for the callbacks from PIN.
*   The app (atfork_callbacks_app.cpp) also prints numbers for each of the pthreads callbacks.
*
*   The before-fork callbacks are atfork_prepare() and pintool_on_fork_before()
*   atfork_prepare() should precede pintool_on_fork_before()
*
*   The after-fork callbacks for PARENT are atfork_parent() and pintool_on_fork_after_in_parent()
*   pintool_on_fork_after_in_parent() should precede after-fork()
*
*   The after-fork callbacks for CHILD are atfork_child() and pintool_on_fork_after_in_child()
*   pintool_on_fork_after_in_child() should precede atfork_child()
*
************************************************/

static void pintool_on_fork_before(UINT32 pid, VOID *param)
{
    fork_callbacks* callbacks = get_shared_object();
    ASSERTX(callbacks);

    if (callbacks->atfork_before == 0)
    {
        cerr << "pintool_on_fork_before() was called before atfork_prepare()" << endl;
        PIN_ExitProcess(1);
    }
    callbacks->pin_before_fork = 1;
}

static void pintool_on_fork_after_in_parent(UINT32 pid, VOID *param)
{
    fork_callbacks* callbacks = get_shared_object();
    ASSERTX(callbacks);

    if (callbacks->atfork_after_parent == 1)
    {
        cerr << "atfork_parent() was called before pintool_on_fork_after_in_parent()" << endl;
        PIN_ExitProcess(1);
    }
    callbacks->pin_after_fork_parent = 1;
}

static void pintool_on_fork_after_in_child(UINT32 pid, VOID *param)
{
    fork_callbacks* callbacks = get_shared_object();
    ASSERTX(callbacks);

    if (callbacks->atfork_after_child == 1)
    {
        cerr << "atfork_parent() was called before pintool_on_fork_after_in_parent()" << endl;
        PIN_ExitProcess(1);
    }
    callbacks->pin_after_fork_child = 1;
}



int main(int argc, char *argv[])
{
    if( PIN_Init(argc,argv) ) return 1;

    PIN_AddForkFunctionProbed(FPOINT_BEFORE, pintool_on_fork_before, 0);
    PIN_AddForkFunctionProbed(FPOINT_AFTER_IN_PARENT, pintool_on_fork_after_in_parent, 0);
    PIN_AddForkFunctionProbed(FPOINT_AFTER_IN_CHILD, pintool_on_fork_after_in_child, 0);

    PIN_StartProgramProbed();

    return 0;
}
