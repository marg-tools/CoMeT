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

#include <stdio.h>
#include <semaphore.h>

int main()
{
    sem_t sem;
    sem_init(&sem, 0, 10);
    int res = sem_post(&sem);
    if (res != 0)
    {
        printf("sem_post result is not 0\n");
        sem_destroy(&sem);
        return -1;
    }
    sem_destroy(&sem);
    
    return 0;
}
