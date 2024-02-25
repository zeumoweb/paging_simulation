#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "replacement_algorithms.h"

typedef struct Process {
    int processID;
    double A;
    double B;
    double C;
    int numberOfFaults;
    int currentAddress;
    int currentReferenceNumber;
    int numberOfEvictions;
    bool isFinished;
    int totalResidencyTime;
} Process;


Process *createProcess(int processID, double a, double b, double c, int numberOfFaults, int currentAddress, int currentReferenceNumber, int numberOfEvictions, bool isFinished, int totalResidencyTime);


// Destructor for Process struct
void freeProcess(Process *process);


/**
 * Determines the current page accessed by the process.
 *
 * @param process Pointer to the Process object being updated.
 * @param pageSize The size of each page in words.
 * @return The page number to be accessed.
 */
int getCurrentPage(Process *process, int pageSize);


/**
 * Determines and sets the next word to be accessed by the process,
 * simulating memory access patterns and updating the process state.
 *
 * @param process Pointer to the Process object being updated.
 * @param randomNumber Random number used to influence the next word selection.
 * @param PROCESS_SIZE The total size of the process memory in words.
 * @param NUMBER_OF_REFERENCES_PER_PROCESS The expected number of references per process.
 */
void setNextReferencedAddress(Process *process, int randomNumber, int PROCESS_SIZE, int NUMBER_OF_REFERENCES_PER_PROCESS);

void printOutput(Process **process_queue, int GLOBAL_EVICTIONS, int num_process);

// Function to check if all processes are done
bool areAllProcessesFinished(Process **process_queue, int SIZE);

// Function to handle page fault
int handlePageFault(bool IS_VERBOSE, Process **process_queue, FrameTableEntry **frame_table, int TOTAL_NUMBER_OF_PAGES, int PAGE_SIZE, int CURRENT_TIME, int *GLOBAL_EVICTIONS, int process_id, int current_page);

void freeProcessQueue(Process **process_queue, int SIZE);