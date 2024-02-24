// Structure for page table entries
typedef struct {
    int valid;
    int frame_number; //represents an address to the inner page tables when being used for the outer page table
} page_entry_t;
