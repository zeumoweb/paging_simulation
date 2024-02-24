#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//initialising variables and functions
int VirtualMemory = 0;
int outerPageSize = 0;
int innerPageSize = 0;
int offset = 0;
void getVirtualMemory(int vSize);
void calculatePageDetails();
void initialisePageTables();
void freePageTables();

//creating structure for first-level table entry
typedef struct {
    int valid_bit;
    int second_level_address;
} OuterPageEntry;

//creating structure for second-level table entry
typedef struct {
    int valid_bit;
    int frame_number;
} InnerPageEntry;

//creating pointers for dynamic arrays
OuterPageEntry* OuterPageTable;
InnerPageEntry* InnerPageTable;

//obtaining virtual memory from main file
void getVirtualMemory(int vSize){
    VirtualMemory = vSize;
}

//calculating the page details
void calculatePageDetails(){
    offset = (int)(VirtualMemory/4);
    int tableSize = (int)((VirtualMemory - offset)/2);
    outerPageSize= tableSize;
    innerPageSize = tableSize;
}

//initialising the values in the page table
void initialisePageTables(){

    //dynamically allocating memory for the two pages
    OuterPageTable = (OuterPageEntry*) malloc(outerPageSize * sizeof(OuterPageEntry));
    InnerPageTable = (InnerPageEntry*) malloc(innerPageSize * sizeof(InnerPageEntry));
    
    //checking if memory allocation was successful
    if (OuterPageTable == NULL || InnerPageTable == NULL){
        fprintf(stderr, "Memory Allocation error!\n");
        exit(EXIT_FAILURE);
    }

    //initialising entries
    for (int i=0; i < outerPageSize; i++){
        OuterPageTable[i].valid_bit = 0;
        OuterPageTable[i].second_level_address = -1;
        InnerPageTable[i].valid_bit = 0;
        InnerPageTable[i].frame_number = -1;
    }
}


void freePageTables(){
    free(OuterPageTable);
    free(InnerPageTable);
}

int main(){
    getVirtualMemory(pow(2,4));
    calculatePageDetails();
    initialisePageTables();
    freePageTables();

return 0;
}
