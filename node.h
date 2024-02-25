//structure for node in linked list
struct Node {
    int frameNum;
    struct Node* next;
};

struct Node* createNode (int frameNum);
void printList(struct Node* head);
void insertAtEnd(struct Node** head, struct Node** tail, int frameNum);
int removeMiddle(struct Node **head, struct Node **tail, int value);
int removeAtBeginning(struct Node **head, struct Node **tail);
void freeList(struct Node* head);
int isValuePresent(struct Node* head, int processNum);

