#include<stdio.h>
//#include "/home/shailja/workspace/research_2020/sniper/include/sim_api.h"
#include "sim_api.h"
#include<stdlib.h>
// #define LENGTH (524288)
#define LENGTH (524288/2)

int main()
{
    int array[LENGTH], array1[LENGTH];
    //SimRoiStart();
    for(register int i = 0; i < LENGTH; i++){
        array1[i] = rand() % 1024;
    }
    SimRoiStart();
    for(register int i = 0; i < LENGTH; i++){
        array[i] = rand() % 1024;
    }

    for(register int i = 0; i < LENGTH; i++){
        array[i] = array[LENGTH-i]; //Re-use
    }
    SimRoiEnd();

    return 0;
}

