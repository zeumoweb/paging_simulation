#include "process.h"
#include "utils_functions.h"

// Constructor for Process struct
Process *createProcess(int processID, double a, double b, double c, int numberOfFaults, int currentAddress, int currentReferenceNumber, int numberOfEvictions, bool isFinished, int totalResidencyTime) {
    Process *process =  (Process*) malloc(sizeof(Process));
    if (process == NULL) {
        fprintf(stderr, "Memory allocation failed for process\n");
        exit(1);
    }

    process->processID = processID;
    process->A = a;
    process->B = b;
    process->C = c;
    process->currentAddress = currentAddress;
    process->currentReferenceNumber = currentReferenceNumber;
    process->numberOfFaults = numberOfFaults;
    process->numberOfEvictions = numberOfEvictions;
    process->isFinished = isFinished;
    process->totalResidencyTime = totalResidencyTime;
    return process;
}


void freeProcess(Process *process) {
    free(process);
}


void setNextReferencedAddress(Process *process, int randomNumber, int PROCESS_SIZE, int NUMBER_OF_REFERENCES_PER_PROCESS) {
    double A = process->A;
    double B = process->B;
    double C = process->C;
    double quotient = (double)randomNumber / (double)(INT_MAX + 1.0);

    if (quotient < A) {
        // Case 0: Sequential Access Pattern
        process->currentAddress = (process->currentAddress + 1) % PROCESS_SIZE;
    } else if (quotient < (A + B)) {
        // Case 1: Backward Localized Access Pattern
        process->currentAddress = (process->currentAddress - 5 + PROCESS_SIZE) % PROCESS_SIZE;
    } else if (quotient < (A + B + C)) {
        // Case 2: Forward Localized Access Pattern
        process->currentAddress = (process->currentAddress + 4) % PROCESS_SIZE;
    } else {
        // Case 3: Random Access Pattern
        process->currentAddress = randomNumber % PROCESS_SIZE;
    }

    process->currentReferenceNumber++;
    if (process->currentReferenceNumber > NUMBER_OF_REFERENCES_PER_PROCESS) {
        process->isFinished = true;
    }
}




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
    printf("\n\n\n");
    printf("Individual Process Statisics \n\n");
    for (int i = 0; i < num_process; ++i)
    {
        Process *currentProcess = process_queue[i];
        totalNumberOfFaults += currentProcess->numberOfFaults;
        printf("Process %d had %d faults", currentProcess->processID + 1, currentProcess->numberOfFaults);

        if (currentProcess->numberOfEvictions > 0)
        {
            printf(" and %.1f average residency \n",
                   (double)currentProcess->totalResidencyTime / currentProcess->numberOfEvictions);
            totalResidencySum += currentProcess->totalResidencyTime;
        }
        else
        {
            printf(".\n\tWith no evictions, the average residence is undefined. \n");
        }
    }

    printf("\n\n");
    printf("Overall Statistics \n\n");

    printf("\nThe total number of page faults is %d\n", totalNumberOfFaults);
    printf("The total number of evictions is %d\n", GLOBAL_EVICTIONS);
    double miss_rate = (double)(totalNumberOfFaults) / (num_process*process_queue[0]->currentReferenceNumber);
    printf("Hit Rate: %.2f\n", 1 - miss_rate);
    printf("Miss Rate: %.2f\n", miss_rate);


    if (GLOBAL_EVICTIONS != 0)
    {
        printf("The and the overall average residency is %.1f.\n\n",
               (double)totalResidencySum / GLOBAL_EVICTIONS);
    }
    else
    {
        printf(".\n\tWith no evictions, the overall average residence is undefined.\n\n");
    }
}



int handlePageFault(char* replacement_policy, Process **process_queue, FrameTableEntry **frame_table, int TOTAL_NUMBER_OF_PAGES, int PAGE_SIZE, int CURRENT_TIME, int *GLOBAL_EVICTIONS, int process_id, int current_page)
{

    int frameIndex = -1;
    // Page miss: Fault

        printf("Page Fault, ");

    process_queue[process_id]->numberOfFaults++;
    if (frameTableIsFull(frame_table, TOTAL_NUMBER_OF_PAGES))
    {
        // Page table is full, Evict a frame based on a replacement policy
        FrameTableEntry *evictedFrame = evict(replacement_policy, frame_table, TOTAL_NUMBER_OF_PAGES, GLOBAL_EVICTIONS);

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
            process_id, current_page, false, false,
            CURRENT_TIME, evictedFrameIndex, true);

        frame_table[evictedFrameIndex] = newFrame;


            printf("Evicting page %d of process id #%d from frame %d \n",
                   evictedPage, evictedFrame->processNumber + 1, evictedFrameIndex);
        frameIndex = evictedFrameIndex;
    } // End of dealing with page miss: page table was full, page was evicted
    else
    {
        // when page is brought in, OS resets R = M = 0 (R == referenced, M == modified)
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
                process_id, current_page, false, false,
                CURRENT_TIME, indexOdHighestFreeFrame, true);


                printf("Using free frame %d\n", indexOdHighestFreeFrame);
            
            frameIndex = indexOdHighestFreeFrame;
        }
        
    } 

    return frameIndex;
}


void freeProcessQueue(Process **process_queue, int SIZE){
    for (int i = 0; i < SIZE; i++){
        freeProcess(process_queue[i]);
    }
    free(process_queue);
}