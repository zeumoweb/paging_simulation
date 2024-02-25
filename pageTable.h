#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//initialising variables and functions
int VirtualMemory = 0;
int numPageEntries = 0; //number of entries for the outer and inner pages
int offset = 0;
void getVirtualMemory(int vSize);
void calculatePageDetails();
void initialisePageTables();
void printInnerPageTable();
void printOuterPageTable();
void freePageTables();

// Structure for page table entries
typedef struct {
    int valid;
    int frame_number; //represents an address to the inner page tables when being used for the outer page table
} page_entry_t;

