#include "utils_functions.h"


page_entry_t *get_page_entry(int logical_address, page_entry_t *L1_table, page_entry_t **L2_tables, int l1_size, int l2_size, int page_size)
{

    // Extract L1_page_number, L2_page_number, and offset from logical address
    int L1_page_number = (logical_address >> (bitLength(l1_size - 1) + bitLength(page_size - 1))) & (l1_size - 1);
    int L2_page_number = (logical_address >> bitLength(page_size - 1)) & (l2_size - 1);
    int offset = logical_address & (page_size - 1);

    // Check if L1 page table entry is valid
    if (!L1_table[L1_page_number].valid)
    {
        // Page fault
        return NULL;
    }

    page_entry_t *L2_table = L2_tables[L1_page_number];
    // Check if L2 page table entry is valid
    if (!L2_table[L2_page_number].valid)
    {
        return NULL;
    }

    // Get L2 page table address from L1 entry
    page_entry_t *page_entry = L2_tables[L1_table[L1_page_number].frame_number];
    return page_entry;
}

int get_physical_address(int logical_address, page_entry_t *L1_table, page_entry_t **L2_tables, int l1_size, int l2_size, int page_size)
{
    page_entry_t *page_entry = get_page_entry(logical_address, L1_table, L2_tables, l1_size, l2_size, page_size);
    if (page_entry == NULL)
    {
        return -1;
    }

    int offset = logical_address & (page_size - 1);
    int physical_address = page_entry->frame_number * page_size + offset;
    return physical_address;
}

int get_page_number(int logical_address, page_entry_t *L1_table, page_entry_t **L2_tables, int l1_size, int l2_size, int page_size)
{

    // Extract L1_page_number, L2_page_number, and offset from logical address
    int L1_page_number = (logical_address >> (bitLength(l1_size - 1) + bitLength(page_size - 1))) & (l1_size - 1);
    int L2_page_number = (logical_address >> bitLength(page_size - 1)) & (l2_size - 1);
    int offset = logical_address & (page_size - 1);

    return L2_page_number;
}

void insertToPageTables(int logical_address, page_entry_t *L1_table, page_entry_t **L2_tables, int l1_size, int l2_size, int page_size, int frame_number)
{

    // Extract L1_page_number, L2_page_number, and offset from logical address
    int L1_page_number = (logical_address >> (bitLength(l1_size - 1) + bitLength(page_size - 1))) & (l1_size - 1);
    int L2_page_number = (logical_address >> bitLength(page_size - 1)) & (l2_size - 1);
    int offset = logical_address & (page_size - 1);

    // Allocate memory for page table if needed
    if (!L1_table[L1_page_number].valid)
    {
        L1_table[L1_page_number].valid = true;
        L1_table[L1_page_number].frame_number = L2_page_number;
    }

    // Update page table entry
    L2_tables[L1_page_number][L2_page_number].valid = true;
    L2_tables[L1_page_number][L2_page_number].frame_number = frame_number;
}

// Function to calculate the bit length of an integer
int bitLength(int n)
{
    int length = 0;
    while (n != 0)
    {
        n >>= 1;
        length++;
    }
    return length;
}

int generateRandomNumberInRange(int lowerBound, int upperBound)
{
    if (lowerBound > upperBound)
    {
        fprintf(stderr, "Error: Lower bound cannot be greater than upper bound.\n");
        exit(1);
    }

    srand(time(NULL));

    // Generate a random number within the inclusive range
    int randomNumber = (rand() % (upperBound - lowerBound + 1)) + lowerBound;

    return randomNumber;
}



void validateArgs(int argc, char *argv[]) {
    if (argc != 9) {
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



void setFlags(int argc, char *argv[], int *MACHINE_SIZE, int *PAGE_SIZE, int *PROCESS_SIZE, int *MEMORY_ACCESS_PATTERN, int *NUMBER_OF_REFERENCES_PER_PROCESS, int *NUMBER_OF_PROCESS, bool *IS_VERBOSE, char **REPLACEMENT_ALGORITHM, int *TOTAL_NUMBER_OF_PAGES) {
    *MACHINE_SIZE = atoi(argv[1]);
    *PAGE_SIZE = atoi(argv[2]);
    *PROCESS_SIZE = atoi(argv[3]);
    *MEMORY_ACCESS_PATTERN = atoi(argv[4]);
    *NUMBER_OF_REFERENCES_PER_PROCESS = atoi(argv[5]);
    *NUMBER_OF_PROCESS = atoi(argv[6]);
    *IS_VERBOSE = (atoi(argv[7]) == 1);  // Invert logic
    *REPLACEMENT_ALGORITHM = argv[8];

    *TOTAL_NUMBER_OF_PAGES = (int)ceil((double)*MACHINE_SIZE / *PAGE_SIZE);
}
