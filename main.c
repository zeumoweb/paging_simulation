#include <string.h>
#include <stdbool.h>
#include "process.h"
#include "frame.h"
#include "utils_functions.h"

int main(int argv, char *argc[])
{
    // Todo : Populate the values using the global simulation flags
    bool IS_RANDOM = false;                                       // Whether or not to show the random integer generation
    int MACHINE_SIZE = 20;                                        // M: Machine size in words
    int PAGE_SIZE = 10;                                           // P: Page size in words
    int PROCESS_SIZE = 10;                                        // S: The size of a process (references are to virtual addresses 0..S-1)
    int JOB_MIX_NUMBER = 1;                                       // J: The job mix, that determines A, B, & C below
    int NUMBER_OF_REFERENCES_PER_PROCESS = 10;                    // N: the number of references for each process
    char *REPLACEMENT_ALGORITH = "random";                        // R: The replacement policy lifo, random, or lru
    bool IS_VERBOSE = true;                                       // Whether or not to show debugging steps
    int GLOBAL_QUANTUM = 3;                                       // Global initial quantum value for round robin (driver)
    int TOTAL_NUMBER_OF_PAGES = (double)MACHINE_SIZE / PAGE_SIZE; // Number of frames
    int page_length = 10;
    int GLOBAL_EVICTIONS = 0;
    int InnerPageTableSize = 5;
    int OuterPageTableSize = 5;

    // Initialize the frame table and process queue
    FrameTableEntry **frame_table = malloc(sizeof(FrameTableEntry *) * TOTAL_NUMBER_OF_PAGES);
    Process **process_queue = malloc(sizeof(Process *) * 4);

    // Initialize Two level page table
    page_entry_t *outer_page_table = createOuterPageTable(OuterPageTableSize);
    page_entry_t **inner_page_tables = createInnerPageTable(InnerPageTableSize, page_length);

    // Initialises the frame table with all frames
    for (int i = 0; i < TOTAL_NUMBER_OF_PAGES; ++i)
    {
        frame_table[i] = createFrameTableEntry(-1, -1, false, false, -1, -1, false);
    }

    for (int i = 0; i < 4; ++i)
    {
        process_queue[i] = createProcess(i, 1, 0, 0, 0, 111 % PROCESS_SIZE, 1, 0, false, 0);
    }

    // process_queue[0] = createProcess(1, 1, 0, 0, 0, 111 % PROCESS_SIZE, 1, 0, false, 0);
    int CURRENT_TIME = 1;

    /* Eviction Policy: random globals */
    int randomReplacementNumber = 0;

    int Num_process = 4;

    while (!areAllProcessesFinished(process_queue, Num_process))
    {
        for (int i = 0; i < Num_process; ++i)
        {
            if (process_queue[i]->isFinished)
                break;
            
            int current_page = get_page_number(process_queue[i]->currentAddress, outer_page_table, inner_page_tables, InnerPageTableSize, OuterPageTableSize, PAGE_SIZE);
            int randomNumber = generateRandomNumberInRange(124313650, 124313650 + 100000); // ToDo: Get random number from file or generate it
            // setNextReferencedAddress(process_queue[i], randomNumber, 5, NUMBER_OF_REFERENCES_PER_PROCESS);
            if (IS_VERBOSE)
            {
                printf("Process #%d references word %d (page %d) at time %d: ", i + 1, process_queue[i]->currentAddress, current_page, CURRENT_TIME);
            }

            // page table hit
            if (frameTableIsHit(frame_table, process_queue[i]->processID, current_page, TOTAL_NUMBER_OF_PAGES))
            {
                // frame table  is hit
                int hitIndex = hitFrame(frame_table, process_queue[i]->processID, current_page, TOTAL_NUMBER_OF_PAGES);
                frame_table[hitIndex]->isLoaded = true;

                if (IS_VERBOSE)
                {
                    printf("Hit in frame %d\n", hitFrame(frame_table, process_queue[i]->processID, current_page, TOTAL_NUMBER_OF_PAGES));
                }
            }
            else
            {
                // page table miss
                int frame_index = handlePageFault(IS_VERBOSE, process_queue, frame_table, TOTAL_NUMBER_OF_PAGES, PAGE_SIZE, CURRENT_TIME, &GLOBAL_EVICTIONS, i, current_page);

                // Update the page tables with the new page
                insertToPageTables(process_queue[i]->currentAddress, outer_page_table, inner_page_tables, InnerPageTableSize, OuterPageTableSize, page_length, frame_index);
            } // End of dealing with page miss

            randomNumber = generateRandomNumberInRange(2013279579, 2013279579 + 100000); // ToDo: Get random number from file or generate it

            // Update the next address/process that the proess will access
            setNextReferencedAddress(process_queue[i], randomNumber, PROCESS_SIZE, NUMBER_OF_REFERENCES_PER_PROCESS);

            // Outputs the random number if flag is given
            if (IS_RANDOM)
                printf("%d used random number: %d\n", i + 1, randomNumber);

            // Outputs the random number the evictRandom call uses
            // TODO: Styve Complete this
            // if ((REPLACEMENT_ALGORITHM == "random" ) && (willEvictRandomNext(i, currentReference)))
            // {
            //     randomReplacementNumber = getRandomNumber(lineScanner);
            //     if (IS_RANDOM)
            //         System.out.printf("%d uses random number: %d\n", (i + 2) % process_queue.size(), randomReplacementNumber);
            // }
            // else if ((process_queue.get((i) % process_queue.size()).isFinished()) && (i != process_queue.size() - 1))
            // {
            //     randomReplacementNumber = getRandomNumber(lineScanner);
            //     if (IS_RANDOM)
            //         System.out.printf("%d uses random number: %d\n", i + 2, randomReplacementNumber);
            // }
            ++CURRENT_TIME;
        }
    }

    // Display General Statistics
    printOutput(process_queue, GLOBAL_EVICTIONS, Num_process);

    // Free all used memory
    freePageTables(inner_page_tables, outer_page_table, InnerPageTableSize);
    freeFrameTable(frame_table, TOTAL_NUMBER_OF_PAGES);
    freeProcessQueue(process_queue, Num_process);
    return 0;
}
