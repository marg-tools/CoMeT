#include<stdio.h>
//#include "/home/shailja/workspace/research_2020/sniper/include/sim_api.h"
#include "sim_api.h"
#include<stdlib.h>

int main()
{
    int array[262144], array1[262144];
    for(register int i = 0; i < 262144; i++){
        array1[i] = rand() % 1024;
    }
    SimRoiStart();
    for(register int i = 0; i < 262144; i++){
        array[i] = rand() % 1024;
    }

    for(register int i = 0; i < 262144; i++){
        array[i] = array[262144-i]; //Re-use
    }
    SimRoiEnd();

    return 0;
}

