#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 32

typedef struct N {
    char data[SIZE];
    struct N* next;
} Node;

Node* getNewHead() {
    return NULL;
}

Node* addNodeToStart(Node* head, char data[]) {
    Node *n = NULL;
    
    n = (Node *)malloc(sizeof(Node));
    if (n == NULL) {
        printf("Failed to allocate memory");
        return NULL;
    }
    
    strncpy(n->data, data, SIZE + 1);
    
    if (head == NULL) {
        head = n;
        n->next = NULL;
    } else {
        n->next = head;
        head = n;
    }

    return n;
}

Node* removeNodeFromStart(Node* head) {
    if (NULL == head) return NULL;
    
    Node* next = NULL;
    next = head->next;
    free(head);

    return head->next;
}

void printList(Node* head) {
    if(head == NULL) {
        printf("List is empty");
        return;
    }
    Node* current = head;
    while(current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}