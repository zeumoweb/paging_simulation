#include "pageTable.h"

page_entry_t* createOuterPageTable(int num_entry){
    page_entry_t* OuterPageTable = (page_entry_t*) malloc(num_entry * sizeof(page_entry_t));
    if (OuterPageTable == NULL){
        fprintf(stderr, "Memory Allocation error!\n");
        exit(EXIT_FAILURE);
    }

    //initialising entries
    for (int i=0; i < num_entry; i++){
        OuterPageTable[i].valid = 0;
        OuterPageTable[i].frame_number = -1;
    }
    return OuterPageTable;
}

page_entry_t** createInnerPageTable(int num_entry, int num_page_table_entries){
    page_entry_t** InnerPageTable = (page_entry_t**) malloc(num_entry * sizeof(page_entry_t*));
    if (InnerPageTable == NULL){
        fprintf(stderr, "Memory Allocation error!\n");
        exit(EXIT_FAILURE);
    }

    //initialising entries
    for (int i=0; i < num_entry; i++){
        //initialising the inner page table for each entry in the outer table
        InnerPageTable[i] = (page_entry_t*) malloc(num_page_table_entries * sizeof(page_entry_t*));
        
        for (int j=0; j < num_entry; j++){
            //allocating memory for each jth entry in the inner page table
            InnerPageTable[i][j].valid = 0;
            InnerPageTable[i][j].frame_number = -1;
        }

    }
    return InnerPageTable;
}


//function to print the inner page tables
void printInnerPageTable(page_entry_t** InnerPageTable, int numPageEntries, int num_page_table_entries) {
    for (int i = 0; i < numPageEntries; i++) {
        for (int j = 0; j < num_page_table_entries; j++) {
            printf("InnerPageTable[%d][%d]: valid_bit=%d, frame_number=%d\n",
                   i, j, InnerPageTable[i][j].valid, InnerPageTable[i][j].frame_number);
        }
        printf("\n");
    }
}


//function to print the outer page tables
void printOuterPageTable(page_entry_t* OuterPageTable, int numPageEntries) {
    for (int i = 0; i < numPageEntries; i++) {
        printf("OuterPageTable[%d]: valid_bit=%d, frame_number=%d\n",
               i, OuterPageTable[i].valid, OuterPageTable[i].frame_number);
    }
}


void freePageTables(page_entry_t** InnerPageTable, page_entry_t* OuterPageTable, int numPageEntries){
    // Deallocating memory
    for (int i = 0; i < numPageEntries; i++) {
        free(InnerPageTable[i]);
    }
    free(InnerPageTable);
    free(OuterPageTable);

}