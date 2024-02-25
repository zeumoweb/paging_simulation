#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "node.h"

int queueSize = 0; //queue size at present
int totalFrameSize = 0; //total frame entries allowed
int pageMiss = 0;
int pageHit = 0;
struct Node* head = NULL;
struct Node* tail = NULL;

void getTotalSize(int MemorySize);
int LRU(int processNum, int frameNum);