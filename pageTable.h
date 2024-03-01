#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure for page table entries
typedef struct {
    int valid;
    int frame_number; // represents an address to the inner page tables when being used for the outer page table
} page_entry_t;


page_entry_t** createInnerPageTable(int num_entry, int num_page_table_entries);
page_entry_t* createOuterPageTable(int num_entry);
void printInnerPageTable(page_entry_t** InnerPageTable, int numPageEntries, int num_page_table_entries);
void printOuterPageTable(page_entry_t* OuterPageTable, int numPageEntries);
void freePageTables(page_entry_t** InnerPageTable, page_entry_t* OuterPageTable, int numPageEntries);

