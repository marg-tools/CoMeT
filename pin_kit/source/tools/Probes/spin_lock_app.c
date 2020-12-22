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
#include <stdlib.h>
#include <pthread.h>

volatile int lock=0;

static void * child(void * v)
{
    printf("Child: calling pthread_spin_lock()\n");
    sleep(3);
    int locked = pthread_spin_lock( &lock );
    printf("Child: acquired spinlock\n");
    locked = pthread_spin_unlock( &lock );
    printf("Child: released spinlock\n");
    return 0;
}

int main()
{
    pthread_t child_thread;
    
    pthread_spin_init( &lock, PTHREAD_PROCESS_PRIVATE );
    
    printf("Main: calling pthread_spin_lock()\n");
    int locked = pthread_spin_lock( &lock );
    printf("Main: acquired spinlock\n");

    int status = pthread_create(&child_thread, 0, child, 0);
    if (status != 0 )
        printf("Main: could not create chikd thread\n" );
    
    sleep(10);
    
    locked = pthread_spin_unlock( &lock );
    printf("Main: released spinlock\n");
    
    pthread_join(child_thread, 0);
}
