#include "pageTable.h"

//creating pointers for dynamic arrays
page_entry_t* OuterPageTable;
page_entry_t** InnerPageTable;

//obtaining virtual memory from main file
void getVirtualMemory(int vSize){
    VirtualMemory = vSize;
}

//calculating the page details
void calculatePageDetails(){
    offset = (int)(VirtualMemory/4);
    int tableSize = (int)((VirtualMemory - offset)/2);
    numPageEntries = tableSize;
}

//initialising the values in the page table
void initialisePageTables(){

    //dynamically allocating memory for the two pages
    OuterPageTable = (page_entry_t*) malloc(numPageEntries * sizeof(page_entry_t));
    InnerPageTable = (page_entry_t**) malloc(numPageEntries * sizeof(page_entry_t*));
    
    //checking if memory allocation was successful
    if (OuterPageTable == NULL || InnerPageTable == NULL){
        fprintf(stderr, "Memory Allocation error!\n");
        exit(EXIT_FAILURE);
    }

    //initialising entries
    for (int i=0; i < numPageEntries; i++){
        OuterPageTable[i].valid = 0;
        OuterPageTable[i].frame_number = -1;
        
        //initialising the inner page table for each entry in the outer table
        InnerPageTable[i] = (page_entry_t*) malloc(numPageEntries * sizeof(page_entry_t*));
        
        for (int j=0; j < numPageEntries; j++){
            //allocating memory for each jth entry in the inner page table
            InnerPageTable[i][j].valid = 0;
            InnerPageTable[i][j].frame_number = -1;
        }

    }
}

//function to print the inner page tables
void printInnerPageTable() {
    for (int i = 0; i < numPageEntries; i++) {
        for (int j = 0; j < numPageEntries; j++) {
            printf("InnerPageTable[%d][%d]: valid_bit=%d, frame_number=%d\n",
                   i, j, InnerPageTable[i][j].valid, InnerPageTable[i][j].frame_number);
        }
        printf("\n");
    }
}

//function to print the outer page tables
void printOuterPageTable() {
    for (int i = 0; i < numPageEntries; i++) {
        printf("OuterPageTable[%d]: valid_bit=%d, frame_number=%d\n",
               i, OuterPageTable[i].valid, OuterPageTable[i].frame_number);
    }
}

void freePageTables(){
    // Deallocating memory
    for (int i = 0; i < numPageEntries; i++) {
        free(InnerPageTable[i]);
    }
    free(InnerPageTable);
    free(OuterPageTable);

}

// int main(){
//     getVirtualMemory(pow(2,4));
//     calculatePageDetails();
//     initialisePageTables();
//     printOuterPageTable();
//     printf("\n\n");
//     printInnerPageTable();
//     freePageTables();

// return 0;
// }
