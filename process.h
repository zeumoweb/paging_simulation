#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Process {
    int processID;
    double A;
    double B;
    double C;
    int numberOfFaults;
    int currentWord;
    int currentReferenceNumber;
    int numberOfEvictions = 0;
    bool isFinished;
    int totalResidencyTime = 0;
} Process;


Process *createProcess(int processID, double a, double b, double c, int currentWord, int currentReferenceNumber);


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
void setNextReferencedWord(Process *process, int randomNumber, int PROCESS_SIZE, int NUMBER_OF_REFERENCES_PER_PROCESS);