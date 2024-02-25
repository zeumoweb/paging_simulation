#include "process.h"

// Constructor for Process struct
Process *createProcess(int processID, double a, double b, double c, int numberOfFaults, int currentWord, int currentReferenceNumber, int numberOfEvictions, bool isFinished, int totalResidencyTime) {
    Process *process = malloc(sizeof(Process));
    if (process == NULL) {
        fprintf(stderr, "Memory allocation failed for process\n");
        exit(1);
    }

    process->processID = processID;
    process->A = a;
    process->B = b;
    process->C = c;
    process->currentWord = currentWord;
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


void setNextReferencedWord(Process *process, int randomNumber, int PROCESS_SIZE, int NUMBER_OF_REFERENCES_PER_PROCESS) {
    double A = process->A;
    double B = process->B;
    double C = process->C;
    double quotient = (double)randomNumber / (double)(INT_MAX + 1.0);

    if (quotient < A) {
        // Case 0: Sequential Access Pattern
        process->currentWord = (process->currentWord + 1) % PROCESS_SIZE;
    } else if (quotient < (A + B)) {
        // Case 1: Backward Localized Access Pattern
        process->currentWord = (process->currentWord - 5 + PROCESS_SIZE) % PROCESS_SIZE;
    } else if (quotient < (A + B + C)) {
        // Case 2: Forward Localized Access Pattern
        process->currentWord = (process->currentWord + 4) % PROCESS_SIZE;
    } else {
        // Case 3: Random Access Pattern
        process->currentWord = randomNumber % PROCESS_SIZE;
    }

    process->currentReferenceNumber++;
    if (process->currentReferenceNumber > NUMBER_OF_REFERENCES_PER_PROCESS) {
        process->isFinished = true;
    }
}

int getCurrentPage(Process *process, int pageSize) {
    return process->currentWord / pageSize;
}
