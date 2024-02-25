#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct FrameTableEntry {
    int processNumber;
    int pageNumber;
    bool isLoaded;
    bool isModified;
    int timeAdded;
    int frameTableIndex;
    bool isActive;
} FrameTableEntry;


FrameTableEntry *createFrameTableEntry(int processNumber, int pageNumber, bool isLoaded,
                                             bool isModified, int timeAdded, int frameTableIndex, bool isActive);


void freeFrameTable(FrameTableEntry **frameTable, int numFrames);

// return the index of the frame that was hit or -1 if no frame was hit
int hitFrame(FrameTableEntry **frameTable, int processID, int pageNumber, int numFrames);

// return true if the frame table is hit, false otherwise
bool frameTableIsHit(FrameTableEntry **frameTable, int processID, int pageNumber, int numFrames);

// return true if the frame table is full, false otherwise
bool frameTableIsFull(FrameTableEntry **frameTable, int NUMBER_OF_PAGES);