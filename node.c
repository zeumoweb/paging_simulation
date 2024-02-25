#include <stdio.h>
#include <stdlib.h>
#include "node.h"

//function to create a new node
struct Node* createNode (int processNum, int frameNum){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode != NULL){
        newNode->processNum = processNum;
        newNode->frameNum = frameNum;
        newNode->next = NULL;
    }
    return newNode;
}

//function to print linked list
void printList(struct Node* head){
    while (head != NULL){
        printf("%d -> ", head->processNum);
        head = head->next;
    }
    printf("NULL\n");
}

//function to insert node at the end of the linked list
void insertAtEnd(struct Node** head, struct Node** tail, int processNum, int frameNum){
    struct Node* newNode = createNode(processNum, frameNum);
    if (newNode != NULL){
        if (*tail == NULL){
            //if the list is empty then set both the head and
            //tail to the new node
            *head = *tail = newNode;
        }
        else{
            (*tail)->next = newNode;
            *tail = newNode;
        }
    }

}

//function to remove and return a node
int* removeNodeByValue(struct Node **head, struct Node **tail, int value){
    static int removedData[2]; //an array to store the removed node
    
    if (*head == NULL){
        removedData[0] = -1;
        removedData[1] = -1;
        return removedData;
    }

    struct Node *curr = *head;
    struct Node *prev = NULL;

    while(curr != NULL && curr->processNum != value){ //checking if value is in list
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL){ //value was not found
        removedData[0] = -1;
        removedData[1] = -1;
        return removedData;
    }

    if (prev == NULL){ 
        //checking if node to be removed if is the 
        *head = curr->next;
        if(*head == NULL){ //checking if list becomes empty after node is removed
            *tail = NULL;
        }
    }
    else{
        prev->next = curr->next; //re-link nodes before and after removed node
        if (prev->next == NULL){
            *tail = prev; //updating the tail if the last node was removed
        }
    }

    //remove any link the removedNode may have with the list
    curr->next = NULL;

    removedData[0] = curr->processNum;
    removedData[1] = curr->frameNum;

    //free memory for removed node
    free(curr);

    return removedData;
}

int* removeLRUNode(struct Node **head, struct Node **tail){
    static int removedData[2]; //an array to store the removed node

    if (*head == NULL){
        removedData[0] = -1;
        removedData[1] = -1;
        return removedData;
    }

    struct Node* removedNode = *head;

    //updating the head to the next node
    if (removedNode->next != NULL){ //updating the list if there is more than one node in the list
        *head = removedNode->next;
    }
    else{
        *head = *tail = NULL; //set head and tail to NULL if there was only one node in the list
    }
    
    //remove any link the removedNode may have with the list
    removedNode->next = NULL;

    removedData[0] = removedNode->processNum;
    removedData[1] = removedNode->frameNum;

    //free memory for removed node
    free(removedNode);

    return removedData;
}

//function to free memory occupied by the linked list
void freeList(struct Node* head) {
    struct Node* current = head;
    struct Node* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

//function to check if a particular node (process) exists
int isValuePresent(struct Node* head, int processNum){
    while (head != NULL){
        if (head->processNum == processNum){
            return 1;
        }
        head = head->next; 
    }
    return 0; //if value was not found in the list
}


// int main() {
//     struct Node* head = NULL;
//     struct Node* tail = NULL;

//     // Insert some nodes
//     insertAtEnd(&head, &tail, 1, 0);
//     printList(head);
//     printf("\n\n");
//     insertAtEnd(&head, &tail, 2, 1);
//     insertAtEnd(&head, &tail, 3, 0);

//     // Print the list
//     printf("Original list: ");
//     printList(head);

//     // Remove a node and print the updated list
//     int* removedValue = removeNodeByValue(&head, &tail, 2);
//     printf("Removed node value: %d\n", removedValue[0]);

//     printf("Updated list: ");
//     printList(head);

//     insertAtEnd(&head, &tail, removedValue[0], removedValue[1]);
//     printf("\n Updated list: ");
//     printList(head);

//     // Remove a node and print the updated list
//     removedValue = removeLRUNode(&head, &tail);
//     printf("Removed node value: %d\n", removedValue[0]);

//     printf("\n Updated list: ");
//     printList(head);

//     printf("%d \n", isValuePresent(head, 2));
//     printf("%d \n", isValuePresent(head, 4));

//     freeList(head);

//     return 0;
// }
