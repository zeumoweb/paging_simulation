#include "utils_functions.h"

page_entry_t* get_page_entry(int logical_address, page_entry_t* L1_table, page_entry_t** L2_tables, int l1_size, int l2_size, int page_size) {

    // Extract L1_page_number, L2_page_number, and offset from logical address
    int L1_page_number = (logical_address >> (bitLength(l1_size - 1) + bitLength(page_size - 1))) & (l1_size - 1); 
    int L2_page_number = (logical_address >> bitLength(page_size - 1)) & (l2_size - 1); 
    int offset = logical_address  & (page_size - 1);

    // Get L2 page table address from L1 entry
    page_entry_t* page_entry = L2_tables[L1_table[L1_page_number].frame_number];
    return page_entry;

}

int get_physical_address(int logical_address, page_entry_t* L1_table, page_entry_t** L2_tables, int l1_size, int l2_size, int page_size){
    page_entry_t* page_entry = translate_address(logical_address, L1_table, L2_tables, l1_size, l2_size, page_size);
    int offset = logical_address  & (page_size - 1);
    int physical_address = page_entry->frame_number * page_size + offset;
    return physical_address;
}


// Function to calculate the bit length of an integer
int bitLength(int n) {
    int length = 0;
    while (n != 0) {
        n >>= 1; 
        length++;
    }
    return length;
}



