#include "replacement_algorithms.h"
// Function prototypes for eviction strategies (implementations omitted for brevity)
// // Todo: Implement the eviction strategies
FrameTableEntry *evictLRU(){
    return NULL;
};
// FrameTableEntry *evictRandom(FrameTableEntry **frameTable, int num_pages){};
FrameTableEntry *evictLIFO(){
    return NULL;
};

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