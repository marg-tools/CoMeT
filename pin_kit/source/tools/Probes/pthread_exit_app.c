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
#include <assert.h>

void *functionC(void *p0);  

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;  


int main()
{
    int res;
    pthread_t thread1/*, thread2*/;
    
    int param;
    if ( (res = pthread_create( &thread1, NULL, &functionC, &param)) )  
    {
        printf("Thread creation failed: %d\n", res);
        return 1;
    }
/*    if ( (res = pthread_create( &thread2, NULL, &functionC, NULL)) )  
    {
        printf("Thread creation failed: %d\n", res);
        return 1;
}*/
    
    pthread_join( thread1, NULL);
    /*   pthread_join( thread2, NULL);*/
    return 0;
}

void *functionC(void *p0)
{
    pthread_exit(p0);
    printf("ERROR: This code comes after pthread_exit. It should not be executed!\n");
    assert(0);
}
