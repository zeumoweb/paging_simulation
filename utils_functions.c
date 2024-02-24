#include "utils_functions.h"

// Todo: make it dynamic 
#define L1_TABLE_SIZE 1024 // 2^10 entries, 10bits for 32-bit address, 42bits for 64-bit address
#define L2_TABLE_SIZE 1024 // 2^10 entries, 10bits for 32-bit address, 10bits for 64-bit address
#define PAGE_SIZE 4096     // 4KB page size, 12bits for 32-bit address, 12bits for 64-bit address


// Page tables
page_entry_t L1_table[L1_TABLE_SIZE];
page_entry_t L2_tables[L1_TABLE_SIZE][L2_TABLE_SIZE];

// Function to translate logical address to physical address
int translate_address(int logical_address, page_entry_t* L1_table, page_entry_t** L2_tables, int l1_size, int l2_size, int page_size) {

    // Extract L1_page_number, L2_page_number, and offset from logical address
    int L1_page_number = (logical_address >> bitLength(l1_size - 1) + bitLength(page_size - 1)) & (l1_size - 1); 
    int L2_page_number = (logical_address >> bitLength(page_size - 1)) & (l2_size - 1); 
    int offset = logical_address  & (page_size - 1);

    printf("L1 page number: %x\n", L1_page_number);
    printf("L2 page number: %x\n", L2_page_number);
    printf("Offset: %x\n", offset);

    // Check if L1 page table entry is valid
    if (!L1_table[L1_page_number].valid) {
        printf("Page fault: L1 page %d not valid\n", L1_page_number);
        // Todo: Handle page fault here (We can simulate loading page from disk)
        return -1;
    }

    // Get L2 page table address from L1 entry
    page_entry_t* L2_table = L2_tables[L1_page_number];

    // Check if L2 page table entry is valid
    if (!L2_table[L2_page_number].valid) {
        printf("Page fault: L2 page %d not valid\n", L2_page_number);
        // Todo: Handle page fault here or report page fault. We will decide
        return -1;
    }

    // Physical address
    int physical_address = (L2_table[L2_page_number].frame_number * PAGE_SIZE) + offset;

    // Check for address space violation
    if (physical_address >= (L2_table[L2_page_number].frame_number + 1) * PAGE_SIZE) {
        printf("Invalid address: Accessing beyond page boundary\n");
        return -1;
    }

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



