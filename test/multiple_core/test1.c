#include<stdio.h>
#include<stdlib.h>
#include "sim_api.h"

int main()
{
    int *array = (int*) malloc(sizeof(int)*2000000);
    SimRoiStart();
    for(register int i = 0; i < 2000000; i++){
            array[i] = 1;
    }
    SimRoiEnd();
    return 0;
}
