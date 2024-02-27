#include "replacement_algorithms.h"
#include "utils_functions.h"
// Function prototypes for eviction strategies (implementations omitted for brevity)
// // Todo: Implement the eviction strategies
FrameTableEntry *evictLRU(){
    return NULL;
};


FrameTableEntry *evictLIFO(FrameTableEntry **frameTable, int num_frames) {
    int latestIndex = 0;
    int latestTime = 0;

    for (int i = 0; i < num_frames; ++i) {
        if (frameTable[i] != NULL &&
            frameTable[i]->timeAdded > latestTime &&
            frameTable[i]->isActive) {
            latestTime = frameTable[i]->timeAdded;
            latestIndex = i;
        }
    }

    // Remove the evicted frame from the frame table
    FrameTableEntry *evictedFrame = frameTable[latestIndex];
    frameTable[latestIndex] = NULL;

    return evictedFrame;
}


FrameTableEntry *evictFIFO(FrameTableEntry **frameTable, int num_frames) {
    int earliestTime = 0;
    int earliestIndex = INT_MAX;

    for (int i = 0; i < num_frames; ++i) {
        if (frameTable[i] != NULL &&
            frameTable[i]->timeAdded < earliestTime &&
            frameTable[i]->isActive) {
            earliestTime = frameTable[i]->timeAdded;
            earliestIndex = i;
        }
    }

    earliestIndex = (earliestIndex == INT_MAX) ? 0 : earliestIndex;

    // Remove the evicted frame from the frame table
    FrameTableEntry *evictedFrame = frameTable[earliestIndex];
    frameTable[earliestIndex] = NULL;

    return evictedFrame;
}


FrameTableEntry *evictRandom(FrameTableEntry **frameTable, int num_frames)
{
    int randomIndex = generateRandomNumberInRange(0, num_frames - 1);
    return frameTable[randomIndex];
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
    else if (strcmp(replacement_algorithm, "fifo") == 0)
    {
        evictedFrame = evictFIFO(frameTable, numFrames);
    }
    else if (strcmp(replacement_algorithm, "lifo") == 0)
    {
        evictedFrame = evictLIFO(frameTable, numFrames);
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