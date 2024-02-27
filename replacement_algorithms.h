#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frame.h"

// Least Recently Used Replacement Algorithm
FrameTableEntry *evictLRU();

// Last In First Out Replacement Algorithm
FrameTableEntry *evictLIFO(FrameTableEntry **frameTable, int num_frames);

// First In First Out Replacement Algorithm
FrameTableEntry *evictFIFO(FrameTableEntry **frameTable, int num_frames);

// Random Replacement Algorithm
FrameTableEntry *evictRandom(FrameTableEntry **frameTable, int num_pages);

FrameTableEntry *evict(char *replacement_algorithm, FrameTableEntry **frameTable, int numFrames, int *GLOBAL_EVICTIONS);