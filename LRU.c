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

//function to get what the total size queue should be
void getTotalSize(int MemorySize){
    totalFrameSize = MemorySize;
}

//function to perform page replacement
int LRU(int processNum, int frameNum){
    if(queueSize < totalFrameSize){ //checking if queue is not full yet
        if (isValuePresent(head, processNum) == 1){//checking if process is already in memory
            //remove it and put it at the back of the queue to show that it was recently used
            int* removedProcess = removeNodeByValue(&head, &tail, processNum);
            insertAtEnd(&head, &tail, removedProcess[0], removedProcess[1]);
            pageHit += 1;
            return removedProcess[1];
        }
        else{//else insert the new process to the back of the queue
            insertAtEnd(&head, &tail, processNum, frameNum);
            pageMiss += 1;
            queueSize += 1;
            return frameNum;
        }

    }
    else{
        if (isValuePresent(head, processNum) == 1){//checking if process is already in memory
            //remove it and put it at the back of the queue to show that it was recently used
            int* removedProcess = removeNodeByValue(&head, &tail, processNum);
            insertAtEnd(&head, &tail, removedProcess[0], removedProcess[1]);
            pageHit += 1;
            return removedProcess[1];
        }
        else{
            //else remove the LRU process and add the new process
            int* removedProcess = removeLRUNode(&head, &tail); 
            insertAtEnd(&head, &tail, processNum, frameNum);
            pageMiss += 1;
            return removedProcess[1];
        }
    }

}

// int main() {
//     getTotalSize(3); // Set the total frame size to 3

//     // Test with some process numbers
//     printf("%d \n", LRU(1,0));
//     printf("%d \n", LRU(2,0));
//     printf("%d \n", LRU(3,1));


//     printf("Final State of the Queue: ");
//     printList(head);
//     printf("\n\n");
//     printf("%d \n", LRU(2,0));

//     printf("Final State of the Queue: ");
//     printList(head);
//     printf("\n\n");

//     printf("%d \n", LRU(4,2));
//     printf("Final State of the Queue: ");
//     printList(head);
//     printf("\n\n");

//     printf("%d \n", LRU(1,0));
//     printf("Final State of the Queue: ");
//     printList(head);
//     printf("\n\n");

//     printf("%d \n", LRU(1,0));
//     printf("Final State of the Queue: ");
//     printList(head);
//     printf("\n\n");

//     // Print the final state of the queue
//     printf("Final State of the Queue: ");
//     printList(head);

//     // Print statistics
//     printf("Page Hits: %d\n", pageHit);
//     printf("Page Misses: %d\n", pageMiss);

//     // Clean up memory (optional)
//     freeList(head);

//     return 0;
// }
