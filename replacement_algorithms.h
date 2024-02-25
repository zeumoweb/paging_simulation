#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frame.h"

FrameTableEntry *evictLRU();
FrameTableEntry *evictLIFO();
FrameTableEntry *evictRandom(FrameTableEntry **frameTable, int num_pages);
FrameTableEntry *evict(char *replacement_algorithm, FrameTableEntry **frameTable, int numFrames, int *GLOBAL_EVICTIONS);