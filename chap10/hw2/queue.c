#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

// Function to add a new element to the queue
void addq(struct node **head, struct node **tail, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Queue Overflow\n");
        return;
    }
    newNode->data = data;
    newNode->next = NULL;

    if (*tail != NULL) {
        (*tail)->next = newNode;
    }
    *tail = newNode;

    if (*head == NULL) {
        *head = newNode;
    }
}

// Function to delete an element from the queue
int delete(struct node **head, struct node **tail) {
    if (*head == NULL) {
        printf("Queue Underflow\n");
        return -1; // Indicate underflow
    }

    struct node *temp = *head;
    int data = temp->data;
    *head = temp->next;

    if (*head == NULL) {
        *tail = NULL; // Queue is now empty
    }

    free(temp);
    return data;
}

// Function to print the entire queue
void printQueue(struct node *head) {
    if (head == NULL) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue contents: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    struct node *head = NULL; // Initialize head of the queue
    struct node *tail = NULL; // Initialize tail of the queue
    int input;

    printf("Enter numbers to add to the queue. Enter a non-natural number to print the queue and exit:\n");
    while (1) {
        printf("Input: ");
        if (scanf("%d", &input) != 1 || input <= 0) {
            // If non-natural number is entered, print the queue and exit
            printQueue(head);
            break;
        }
        addq(&head, &tail, input);
    }

    // Cleanup: Free remaining nodes
    while (head != NULL) {
        delete(&head, &tail);
    }

    return 0;
}

