#include "utils_functions.h"


page_entry_t *get_page_entry(int logical_address, page_entry_t *L1_table, page_entry_t **L2_tables, int l1_size, int l2_size, int page_size)
{

    // Extract level1_index, level2_index, and offset from logical address
    int level1_index = (logical_address / page_size) / l2_size;
    int level2_index = (logical_address / page_size) % l2_size;
    int offset = logical_address % page_size;

    // Check if L1 page table entry is valid
    if (!L1_table[level1_index].valid)
    {
        // Page fault
        return NULL;
    }

    page_entry_t *L2_table = L2_tables[level1_index];
    // Check if L2 page table entry is valid
    if (!L2_table[level2_index].valid)
    {
        return NULL;
    }

    // Get L2 page table address from L1 entry
    page_entry_t *page_entry = L2_tables[L1_table[level1_index].frame_number];
    return page_entry;
}

int get_physical_address(int logical_address, page_entry_t *L1_table, page_entry_t **L2_tables, int l1_size, int l2_size, int page_size)
{
    page_entry_t *page_entry = get_page_entry(logical_address, L1_table, L2_tables, l1_size, l2_size, page_size);
    if (page_entry == NULL)
    {
        return -1;
    }

    int offset = logical_address % page_size;
    int physical_address = page_entry->frame_number * page_size + offset;
    return physical_address;
}

int get_page_number(int logical_address, page_entry_t *L1_table, page_entry_t **L2_tables, int l1_size, int l2_size, int page_size)
{

    // Extract level1_index, level2_index, and offset from logical address
    int level1_index = (logical_address / page_size) / l2_size;
    int level2_index = (logical_address / page_size) % l2_size;
    int offset = logical_address % page_size;

    return level2_index;
}


void insertToPageTables(int logical_address, page_entry_t *L1_table, page_entry_t **L2_tables, int l1_size, int l2_size, int page_size, int frame_number)
{
    // Extract level1_index, level2_index, and offset from logical address
    int level1_index = (logical_address >> (bitLength(l1_size - 1) + bitLength(page_size - 1))) & (l1_size - 1);
    int level2_index = (logical_address >> bitLength(page_size - 1)) & (l2_size - 1);
    int offset = logical_address % page_size;

    // Allocate memory for page table if needed
    if (!L1_table[level1_index].valid)
    {
        L1_table[level1_index].valid = true;
        L1_table[level1_index].frame_number = level2_index;
    }

    // Update page table entry
    L2_tables[level1_index][level2_index].valid = true;
    L2_tables[level1_index][level2_index].frame_number = frame_number;
}

// Function to calculate the bit length of an integer
int bitLength(int n)
{
    return log2(n) + 1;
}

int generateRandomNumberInRange(int lowerBound, int upperBound)
{
    if (lowerBound > upperBound)
    {
        fprintf(stderr, "Error: Lower bound cannot be greater than upper bound.\n");
        exit(1);
    }


    // Generate a random number within the inclusive range
    int randomNumber = (rand() % (upperBound - lowerBound + 1)) + lowerBound;

    return randomNumber;
}


float random_float_0_1() {
  // Generate a random integer between 0 (inclusive) and RAND_MAX (exclusive)
  int random_int = rand();

  // Convert the integer to a float between 0.0 and 1.0 (inclusive)
  return (double)random_int / (double)RAND_MAX;
}



void validateArgs(int argc, char *argv[]) {
    if (argc != 8) {
        perror("Invalid number of arguments provided. Please provide 8 arguments. \n");
        exit(1);
    }

    int offset = 0;
    for (int i = 1; i < argc - 1; ++i) {
       char* endptr;
        long value = strtol(argv[i], &endptr, 10); 
        if (*endptr != '\0') {
            fprintf(stderr, "Error: Invalid integer at argument %d\n", i + 1);
            exit(1);
        }
        if (value < 0) {  // Check for negative values
            fprintf(stderr, "Error: Input values must be non-negative\n");
            exit(1);
        }
    }
}



void setFlags(int argc, char *argv[], int *MACHINE_SIZE, int *PAGE_SIZE, int *PROCESS_SIZE, int *MEMORY_ACCESS_PATTERN, int *NUMBER_OF_REFERENCES_PER_PROCESS, int *NUMBER_OF_PROCESS, char **REPLACEMENT_ALGORITHM, int *TOTAL_NUMBER_OF_PAGES) {
    *MACHINE_SIZE = atoi(argv[1]);
    *PAGE_SIZE = atoi(argv[2]);
    *PROCESS_SIZE = atoi(argv[3]);
    *MEMORY_ACCESS_PATTERN = atoi(argv[4]);
    *NUMBER_OF_REFERENCES_PER_PROCESS = atoi(argv[5]);
    *NUMBER_OF_PROCESS = atoi(argv[6]);
    *REPLACEMENT_ALGORITHM = argv[7];

    *TOTAL_NUMBER_OF_PAGES = (int)ceil((double)*MACHINE_SIZE / *PAGE_SIZE);
}
