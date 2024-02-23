#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAX_MEMORY_SIZE (1024*1024) // 1MB, 1048576
#define MAX_VIRTUAL_MEMORY_SIZE (1024*1024*1024) // 1GB
#define PAGE_SIZE 4096 // 4KB, frame size


//calculate number of frames
int getNumFrames(int size) {
    return size / PAGE_SIZE;
}

//calculate number of pages 
int getNumPages(int size) {
    return size / PAGE_SIZE;
}

// request memory randomly
int createMemoryAddress(int addressBitSize){
    return rand() % (1 << addressBitSize);
}

void requestRandomMemory(){
    //seed random generator with time 
    srand(time(NULL));

    printf("Generatine a few memory addresses \n");
    for(int i = 0; i < 10; i++){
        printf("Memory address: %d\n", createMemoryAddress(20));
    }
}