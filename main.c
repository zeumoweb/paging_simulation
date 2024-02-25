#include <string.h>
#include <stdbool.h>
#include "process.h"
#include "frame.h"
#include "utils_functions.h"
// #include "pageTable.h"

// Function to check if all processes are done
bool areAllProcessesFinished(Process **process_queue, int SIZE)
{
    // Iterate through the array of processes
    for (int i = 0; i < SIZE; ++i)
    {
        if (!process_queue[i]->isFinished)
            return false;
    }
    return true;
}

// Todo: May be updated to track more statistics
void printOutput(Process **process_queue, int GLOBAL_EVICTIONS, int num_process)
{
    int totalNumberOfFaults = 0;
    int totalResidencySum = 0;

    // Iterate through the processes
    for (int i = 0; i < num_process; ++i)
    {
        Process *currentProcess = process_queue[i];
        totalNumberOfFaults += currentProcess->numberOfFaults;
        printf("Process %d had %d faults", currentProcess->processID, currentProcess->numberOfFaults);

        if (currentProcess->numberOfEvictions > 0)
        {
            printf(" and %.1f average residency\n",
                   (double)currentProcess->totalResidencyTime / currentProcess->numberOfEvictions);
            totalResidencySum += currentProcess->totalResidencyTime;
        }
        else
        {
            printf(".\n\tWith no evictions, the average residence is undefined.");
        }
    }

    printf("\nThe total number of faults is %d", totalNumberOfFaults);

    if (GLOBAL_EVICTIONS != 0)
    {
        printf(" and the overall average residency is %.1f.\n\n",
               (double)totalResidencySum / GLOBAL_EVICTIONS);
    }
    else
    {
        printf(".\n\tWith no evictions, the overall average residence is undefined.\n");
    }
}

// // Function prototypes for eviction strategies (implementations omitted for brevity)
// // Todo: Implement the eviction strategies
FrameTableEntry *evictLRU(){};
// FrameTableEntry *evictRandom(FrameTableEntry **frameTable, int num_pages){};
FrameTableEntry *evictLIFO(){};

FrameTableEntry *evictRandom(FrameTableEntry **frameTable, int num_pages)
{
    return frameTable[6 % num_pages];
}

FrameTableEntry *evict(char *replacement_algorithm, FrameTableEntry **frameTable, int numFrames, int *GLOBAL_EVICTIONS)
{
    FrameTableEntry *evictedFrame = NULL;

    if (strcmp(replacement_algorithm, "lru") == 0)
    {
        evictedFrame = evictLRU();
    }
    else if (strcmp(replacement_algorithm, "random") == 0)
    {
        evictedFrame = evictRandom(frameTable, numFrames);
    }
    else if (strcmp(replacement_algorithm, "lifo") == 0)
    {
        evictedFrame = evictLIFO();
    }
    else
    {
        fprintf(stderr, "Error: invalid replacement algorithm: %s\n", replacement_algorithm);
        exit(1);
    }

    // Increment global evictions only after a successful eviction
    if (evictedFrame != NULL)
    {
        (*GLOBAL_EVICTIONS)++;
    }

    return evictedFrame;
}

int main(int argv, char *argc[])
{
    // Todo : Populate the values using the global simulation flags
    bool IS_RANDOM = true;                                        // Whether or not to show the random integer generation
    int MACHINE_SIZE = 20;                                        // M: Machine size in words
    int PAGE_SIZE = 10;                                           // P: Page size in words
    int PROCESS_SIZE = 10;                                        // S: The size of a process (references are to virtual addresses 0..S-1)
    int JOB_MIX_NUMBER = 1;                                       // J: The job mix, that determines A, B, & C below
    int NUMBER_OF_REFERENCES_PER_PROCESS = 10;                    // N: the number of references for each process
    char *REPLACEMENT_ALGORITH = "random";                        // R: The replacement policy lifo, random, or lru
    bool IS_VERBOSE = true;                                       // Whether or not to show debugging steps
    int GLOBAL_QUANTUM = 3;                                       // Global initial quantum value for round robin (driver)
    int TOTAL_NUMBER_OF_PAGES = (double)MACHINE_SIZE / PAGE_SIZE; // Number of frames
    int page_length = 5;
    int GLOBAL_EVICTIONS = 0;
    int InnerPageTableSize = 5;
    int OuterPageTableSize = 5;

    char *RANDOM_NUMBER_FILE_PATH = "random_gen_numbers.txt";

    // Simulation
    FrameTableEntry **frame_table = malloc(sizeof(FrameTableEntry *) * TOTAL_NUMBER_OF_PAGES);
    Process **process_queue = malloc(sizeof(Process *) * 4);

    // Two level page table
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

    // FILE *fd = fopen(RANDOM_NUMBER_FILE_PATH, "r");
    int Num_process = 4;

    while (!areAllProcessesFinished(process_queue, Num_process))
    {
        for (int i = 0; i < Num_process; ++i)
        {
            if (process_queue[i]->isFinished)
                break;
            int randomNumber = 2013279579; // generateRandomNumberInRange(124313650, 124313650 + 100000); // ToDo: Get random number from file or generate it
            setNextReferencedWord(process_queue[i], randomNumber, 5, NUMBER_OF_REFERENCES_PER_PROCESS);
            int physicalAddress = get_physical_address(process_queue[i]->currentWord, outer_page_table, inner_page_tables, InnerPageTableSize, OuterPageTableSize, page_length);
            if (IS_VERBOSE)
            {
                printf("%d references word %d (page %d) at time %d: \n", i + 1, process_queue[i]->currentWord, getCurrentPage(process_queue[i], PAGE_SIZE), CURRENT_TIME);
            }

           
                // page table hit
                if (frameTableIsHit(frame_table, process_queue[i]->processID, getCurrentPage(process_queue[i], PAGE_SIZE), TOTAL_NUMBER_OF_PAGES))
                {
                    // frame table  is hit
                    puts("Page hit");
                    int hitIndex = hitFrame(frame_table, process_queue[i]->processID, getCurrentPage(process_queue[i], PAGE_SIZE), TOTAL_NUMBER_OF_PAGES);
                    frame_table[hitIndex]->isLoaded = true;

                    if (IS_VERBOSE)
                    {
                        printf("Hit in frame %d\n", hitFrame(frame_table, process_queue[i]->processID, getCurrentPage(process_queue[i], PAGE_SIZE), TOTAL_NUMBER_OF_PAGES));
                    }
                }
                else
                {
                    // Page miss: Fault
                    if (IS_VERBOSE)
                        printf("Page Fault, ");

                    process_queue[i]->numberOfFaults++;
                    if (frameTableIsFull(frame_table, TOTAL_NUMBER_OF_PAGES))
                    {
                        // Page table is full, Evict a frame based on a replacement policy
                        puts("Page table is full, evicting a frame");
                        FrameTableEntry *evictedFrame = evict("random", frame_table, TOTAL_NUMBER_OF_PAGES, &GLOBAL_EVICTIONS);

                        if (evictedFrame == NULL)
                        {
                            printf("Error: no frame was evicted\n");
                            exit(1);
                        }
                        int evictedPage = evictedFrame->pageNumber;
                        int evictedFrameIndex = evictedFrame->frameTableIndex;

                        // Updates the eviction number
                        process_queue[evictedFrame->processNumber]->numberOfEvictions++;

                        // Adds the residency time
                        process_queue[evictedFrame->processNumber]->totalResidencyTime += (CURRENT_TIME - evictedFrame->timeAdded);

                        // Replaces the old frame with the new one
                        FrameTableEntry *newFrame = createFrameTableEntry(
                            i, getCurrentPage(process_queue[i], PAGE_SIZE), false, false,
                            CURRENT_TIME, evictedFrameIndex, true);

                        frame_table[evictedFrameIndex] = newFrame;

                        if (IS_VERBOSE)
                            printf("evicting page %d of %d from frame %d\n",
                                   evictedPage, evictedFrame->processNumber + 1, evictedFrameIndex);
                    } // End of dealing with page miss: page table was full, page was evicted
                    else
                    {
                        // when page is brought in, OS resets R = M = 0 (R == referenced, M == modified)
                        puts("Page table is not full, using free frame");
                        if (frameTableIsFull(frame_table, TOTAL_NUMBER_OF_PAGES))
                        {
                            printf("Error: Table is full but should not be \n");
                            exit(1);
                        }
                        else
                        {
                            // Look for Page table that has free frames
                            FrameTableEntry *highestFreeFrame = NULL;
                            int indexOdHighestFreeFrame = TOTAL_NUMBER_OF_PAGES - 1;
                            for (; indexOdHighestFreeFrame >= 0; --indexOdHighestFreeFrame)
                            {
                                if (!frame_table[indexOdHighestFreeFrame]->isActive)
                                {
                                    highestFreeFrame = frame_table[indexOdHighestFreeFrame];
                                    break;
                                }
                            }

                            if (highestFreeFrame == NULL)
                            {
                                printf("Error: highest free frame could not be found\n");
                                exit(1);
                            }
                            // Replaces the free frame with the new one
                            frame_table[indexOdHighestFreeFrame] = createFrameTableEntry(
                                i, getCurrentPage(process_queue[i], PAGE_SIZE), false, false,
                                CURRENT_TIME, indexOdHighestFreeFrame, true);

                            if (IS_VERBOSE)
                                printf("using free frame %d\n", indexOdHighestFreeFrame);
                        }
                    } // End of dealing with page miss: page table was not full, free frame was used
                }     // End of dealing with page miss

            randomNumber = 2013279579; // ToDo: Get random number from file or generate it
            setNextReferencedWord(process_queue[i], randomNumber, PROCESS_SIZE, NUMBER_OF_REFERENCES_PER_PROCESS);

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
    printOutput(process_queue, GLOBAL_EVICTIONS, Num_process);
    return 0;
}
