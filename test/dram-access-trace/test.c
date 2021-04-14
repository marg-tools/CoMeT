#include<stdio.h>
#include "sim_api.h"
#include<stdlib.h>

int main()
{
    int array[262144];
    
    for(register int i = 0; i < 262144; i++){
        array[i] = rand() % 1024;
    }

    //Array already present in L3 cache; Re-using the same array index so no cache misses for this loop
    for(register int i = 0; i < 262144; i++){
        array[i] = array[262144-i];
    }

    return 0;
}

