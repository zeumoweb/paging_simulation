#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "pageTable.h"
#include <time.h>
#include "process.h"


int bitLength(int n);

// Function to translate logical address to physical address, returns the page table entry that corresponds to the logical address.
page_entry_t* get_page_entry(int logical_address, page_entry_t* L1_table, page_entry_t** L2_tables, int L1_TABLE_SIZE, int L2_TABLE_SIZE, int PAGE_SIZE);

// Function to get the actual physical address from the logical address
int get_physical_address(int logical_address, page_entry_t* L1_table, page_entry_t** L2_tables, int L1_TABLE_SIZE, int L2_TABLE_SIZE, int PAGE_SIZE);

int generateRandomNumberInRange(int lowerBound, int upperBound);

int get_page_number(int logical_address, page_entry_t* L1_table, page_entry_t** L2_tables, int l1_size, int l2_size, int page_size);

// Function to insert a new page into the two level page table
void insertToPageTables(int logical_address, page_entry_t* L1_table, page_entry_t** L2_tables, int l1_size, int l2_size, int page_size, int frame_number);
