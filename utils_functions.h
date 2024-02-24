#include <stdio.h>
#include <stdlib.h>
#include "page_structures.h"


int bitLength(int n);
int translate_address(int logical_address, page_entry_t* L1_table, page_entry_t** L2_tables, int L1_TABLE_SIZE, int L2_TABLE_SIZE, int PAGE_SIZE);
