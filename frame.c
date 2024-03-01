#include "frame.h"
#include "utils_functions.h"

FrameTableEntry *createFrameTableEntry(int processNumber, int pageNumber, bool isLoaded,
                                       bool isModified, int timeAdded, int frameTableIndex, bool isActive)
{
    FrameTableEntry *entry = (FrameTableEntry*) malloc(sizeof(FrameTableEntry));
    if (entry == NULL)
    {
        fprintf(stderr, "Memory allocation failed for FrameTableEntry\n");
        exit(1);
    }

    entry->processNumber = processNumber;
    entry->pageNumber = pageNumber;
    entry->isLoaded = isLoaded;
    entry->isModified = isModified;
    entry->timeAdded = timeAdded;
    entry->frameTableIndex = frameTableIndex;
    entry->isActive = isActive;
    return entry;
}

void freeFrameTable(FrameTableEntry **frameTable, int numFrames)
{
    for (int i = 0; i < numFrames; ++i)
    {
        free(frameTable[i]);
    }
    free(frameTable);
}

bool frameTableIsHit(FrameTableEntry **frameTable, int processID, int pageNumber, int numFrames)
{
    for (int i = 0; i < numFrames; ++i)
    {
        if (frameTable[i]->processNumber == processID &&
            frameTable[i]->pageNumber == pageNumber &&
            frameTable[i]->isActive)
        {
            return true;
        }
    }
    return false;
}

int hitFrame(FrameTableEntry **frameTable, int processID, int pageNumber, int numFrames)
{
    for (int i = 0; i < numFrames; ++i)
    {
        if (frameTable[i]->processNumber == processID &&
            frameTable[i]->pageNumber == pageNumber &&
            frameTable[i]->isActive)
        {
            return i;
        }
    }
    return -1;
}



bool frameTableIsFull(FrameTableEntry **frameTable, int TOTAL_NUMBER_OF_FRAMES)
{
    int numberOfActivePages = 0;
    for (int i = 0; i < TOTAL_NUMBER_OF_FRAMES; ++i)
    {
        if (frameTable[i]->isActive)
        {
            numberOfActivePages++;
        }
    }
    return numberOfActivePages == TOTAL_NUMBER_OF_FRAMES;
}
