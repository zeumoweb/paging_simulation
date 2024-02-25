#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "node.h"


//function to perform page replacement
int LRU(struct Node** head, struct Node** tail, int frameNum){
    if (isValuePresent(*head, frameNum) == 1){//checking if process is already in memory
        //remove it and put it at the back of the queue to show that it was recently used
        int removedFrame = removeMiddle(head, tail, frameNum);
        insertAtEnd(head, tail, removedFrame);
        return removedFrame;
    }
    else{
        //else remove the LRU process and add the new process
        int removedFrame = removeAtBeginning(head, tail); 
        insertAtEnd(head, tail, frameNum);
        return removedFrame;
    }

}

// int main() {
//     struct Node* head = NULL;
//     struct Node* tail = NULL;

//     insertAtEnd(&head, &tail, 0);
//     insertAtEnd(&head, &tail, 1);
//     insertAtEnd(&head, &tail, 2);
//     insertAtEnd(&head, &tail, 3);
//     insertAtEnd(&head, &tail, 4);

//     printList(head);

//     // // Test with some process numbers
//     printf("%d \n", LRU(&head, &tail,0));
//     printf("%d \n", LRU(&head, &tail,2));
//     printf("%d \n", LRU(&head, &tail,1));


//     printf("Final State of the Queue: ");
//     printList(head);
//     printf("\n\n");
//     printf("%d \n", LRU(&head, &tail,5));

//     printf("Final State of the Queue: ");
//     printList(head);
//     printf("\n\n");


//     // Print the final state of the queue
//     printf("Final State of the Queue: ");
//     printList(head);

//     // Clean up memory (optional)
//     freeList(head);

//     return 0;
// }
