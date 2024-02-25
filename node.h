//structure for node in linked list
struct Node {
    int processNum;
    int frameNum;
    struct Node* next;
};

struct Node* createNode (int processNum, int frameNum);
void printList(struct Node* head);
void insertAtEnd(struct Node** head, struct Node** tail, int processNum, int frameNum);
int* removeNodeByValue(struct Node **head, struct Node **tail, int value);
int* removeLRUNode(struct Node **head, struct Node **tail);
void freeList(struct Node* head);
int isValuePresent(struct Node* head, int processNum);

