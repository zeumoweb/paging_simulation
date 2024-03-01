#include <string.h>
#include <stdbool.h>
#include "process.h"
#include "frame.h"
#include "utils_functions.h"
#include "simulation.h"

// Command Line Order : Machine Size, Page Size, Process Size, Memory Access Pattern, Number of References per Process, Number of Processes, Verbose, Replacement Algorithm

int main(int argv, char *argc[])
{

    srand(time(NULL)); // Seed the random number generator
    // Populate the values using the global simulation flags
    int MACHINE_SIZE;                                              // M: Machine size in words
    int PAGE_SIZE;                                                 // P: Page size in words
    int PROCESS_SIZE;                                              // S: The size of a process (references are to virtual addresses ..S-1)
    int MEMORY_ACCESS_PATTERN;                                     // A: The job mix, that determines A, B, & C below
    int NUMBER_OF_REFERENCES_PER_PROCESS;                          // R : the number of references for each process
    int NUMBER_OF_PROCESS;                                         // N: The number of processes
    char *REPLACEMENT_ALGORITH;                                    // Algo: The replacement policy lifo, random, or lru
    int TOTAL_NUMBER_OF_FRAMES = (double)MACHINE_SIZE / PAGE_SIZE; // Number of frames
    int page_length = 10;
    int GLOBAL_EVICTIONS = 0; // Global evictions counter
    int InnerPageTableSize = 4;
    int OuterPageTableSize = 4;

    int GLOBAL_QUANTUM = 5; // Global initial quantum value for round robin (driver)

    validateArgs(argv, argc);
    setFlags(argv, argc, &MACHINE_SIZE, &PAGE_SIZE, &PROCESS_SIZE, &MEMORY_ACCESS_PATTERN, &NUMBER_OF_REFERENCES_PER_PROCESS, &NUMBER_OF_PROCESS, &REPLACEMENT_ALGORITH, &TOTAL_NUMBER_OF_FRAMES);

    // Initialize the frame table and process queue
    FrameTableEntry **frame_table = initializeFrameTable(TOTAL_NUMBER_OF_FRAMES);
    Process **process_queue = initializeProcessQueue(MEMORY_ACCESS_PATTERN, PROCESS_SIZE, NUMBER_OF_PROCESS);

    // Initialize array to hold the address history of each process
    int **process_address_history = initializeProcessAddressHistory(NUMBER_OF_PROCESS, NUMBER_OF_REFERENCES_PER_PROCESS);

    // Initialize Two level page table
    page_entry_t *outer_page_table = createOuterPageTable(OuterPageTableSize);
    page_entry_t **inner_page_table = createInnerPageTable(InnerPageTableSize, page_length);

    int CURRENT_TIME = 1;

    while (!areAllProcessesFinished(process_queue, NUMBER_OF_PROCESS))
    {
        for (int i = 0; i < NUMBER_OF_PROCESS; ++i)

        {
            // Simulate accessing the same process address repeatedly to enhance reality of simulation
            for (int current_reference = 0; current_reference < GLOBAL_QUANTUM; ++current_reference)
            {
                // Start Round Robin Round for current process
                if (process_queue[i]->isFinished)
                    break;
                int logical_address = process_queue[i]->currentAddress;
                // Randomly pick either the current address of the process or an address in its history.
                float probability = random_float_0_1();
                if (probability < 0.2)
                {
                    int random = generateRandomNumberInRange(0, process_queue[i]->currentReferenceNumber - 1);
                    logical_address = process_address_history[i][random];
                }
                int current_page = get_page_number(logical_address, outer_page_table, inner_page_table, InnerPageTableSize, OuterPageTableSize, PAGE_SIZE);
                int randomNumber = generateRandomNumberInRange(2013279579, 2013279579 + 100000); // ToDo: Get random number from file or generate it

                printf("Process #%d references address 0x%x (page %d) at time %d: ", i + 1, logical_address, current_page, CURRENT_TIME);
                // page table hit
                if (get_physical_address(logical_address, outer_page_table, inner_page_table, OuterPageTableSize, InnerPageTableSize, PAGE_SIZE) != 1 && frameTableIsHit(frame_table, process_queue[i]->processID, current_page, TOTAL_NUMBER_OF_FRAMES))
                {
                    // frame table  is hit
                    int hitIndex = hitFrame(frame_table, process_queue[i]->processID, current_page, TOTAL_NUMBER_OF_FRAMES);
                    frame_table[hitIndex]->isLoaded = true;
                    printf("Hit in frame %d\n", hitIndex);
                }
                else
                {
                    // page table miss
                    int frame_index = handlePageFault(REPLACEMENT_ALGORITH, process_queue, frame_table, TOTAL_NUMBER_OF_FRAMES, PAGE_SIZE, CURRENT_TIME, &GLOBAL_EVICTIONS, i, current_page);

                    // Update the page tables with the new page
                    insertToPageTables(logical_address, outer_page_table, inner_page_table, InnerPageTableSize, OuterPageTableSize, page_length, frame_index);
                } // End of dealing with page miss

                randomNumber = generateRandomNumberInRange(2013279579, 2013279579 + 100000); // ToDo: Get random number from file or generate it

                // Add current process address to its history of addresses
                process_address_history[i][process_queue[i]->currentReferenceNumber] = logical_address;

                // Update the next address/process that the proess will access
                setNextReferencedAddress(process_queue[i], randomNumber, PROCESS_SIZE, NUMBER_OF_REFERENCES_PER_PROCESS);

                ++CURRENT_TIME;
            } // End Round Robin Round
        }
    } // All process completed their execution

    // Display General Statistics
    printOutput(process_queue, GLOBAL_EVICTIONS, NUMBER_OF_PROCESS);

    // Free all used memory
    freePageTables(inner_page_table, outer_page_table, InnerPageTableSize);
    freeFrameTable(frame_table, TOTAL_NUMBER_OF_FRAMES);
    freeProcessQueue(process_queue, NUMBER_OF_PROCESS);
    return 0;
}
