#include "process.h"

// Function to initialize the process queue
Process **initializeProcessQueue(int access_pattern_number, int PROCESS_SIZE, int numProcesses);

// Function to initialize the process address history
int** initializeProcessAddressHistory(int NUMBER_OF_PROCESS, int NUMBER_OF_REFERENCES_PER_PROCESS);

// Function to initialize the frame table
FrameTableEntry** initializeFrameTable(int TOTAL_NUMBER_OF_FRAMES);
