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

#ifndef _ATFORK_CALLBACKS_H_
#define _ATFORK_CALLBACKS_H_

#include <iostream>
#include <errno.h>
#include <sys/shm.h>
using std::cerr;
using std::endl;
using std::cout;

const key_t shm_key = 1234;

typedef struct fork_callbacks_s {
    int atfork_before;
    int atfork_after_child;
    int atfork_after_parent;
    int pin_before_fork;
    int pin_after_fork_child;
    int pin_after_fork_parent;
} fork_callbacks;

inline fork_callbacks* get_shared_mem(bool create)
{
    int shmid = shmget(shm_key, sizeof(fork_callbacks), create ? IPC_CREAT | 0666 : 0666);
    if (shmid < 0)
    {
        cerr << "shmget failed with errno " << errno << endl;
        return NULL;
    }

    void* shm = shmat(shmid, NULL, 0);
    if (shm == (void*) -1) {
        cerr << "shmat failed with errno " << errno << endl;
        return NULL;
    }

    return (fork_callbacks*)shm;
}

inline bool remove_shared_object(bool silent = false)
{
    int shmid = shmget(shm_key, sizeof(fork_callbacks), 0666);
    if (shmid < 0)
    {
        if (!silent)
            cerr << "shmget failed with errno " << errno << endl;
        return false;
    }

    void* shm = shmat(shmid, NULL, 0);
    if (shm == (void*) -1) {
        if (!silent)
            cerr << "shmat failed with errno " << errno << endl;
        return false;
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        if (!silent)
            cerr << "shmctl failed with errno " << errno << endl;
        return false;
    }

    if (shmdt(shm) == -1)
    {
        if (!silent)
            cerr << "shmdt failed with errno " << errno << endl;
        return false;
    }

    return true;

}

inline fork_callbacks* create_shared_object()
{
    fork_callbacks* ret = NULL;
    remove_shared_object( true );
    ret = get_shared_mem( true );
    if (ret == NULL)
    {
        remove_shared_object( true );
    }
    return ret;
}

inline fork_callbacks* get_shared_object()
{
    fork_callbacks* ret = NULL;
    ret = get_shared_mem( false );
    if (ret == NULL)
    {
        remove_shared_object( true );
    }
    return ret;
}

#endif
