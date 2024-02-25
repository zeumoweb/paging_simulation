//initialising variables and functions
int PhysicalMemory = 0;


//structure for physical memory address
typedef struct{
    int processNum;
    int pageNum;
    bool isLoaded;
    bool isModified;
    int timeAdded;
    int frameTableIndex;
    bool isActive;
} frame_entry;
