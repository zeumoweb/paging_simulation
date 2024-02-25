#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>


// request memory randomly
int createMemoryAddress(int addressBitSize){
    return rand() % (1 << addressBitSize);
}

void requestRandomMemory(int numRequests){
    //seed random generator with time 
    srand(time(NULL));

    printf("Generatine a few memory addresses \n");
    for(int i = 0; i < numRequests; i++){
        printf("Memory address: %d\n", createMemoryAddress(20));
    }
}