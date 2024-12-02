#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

// Push function to add an element to the stack
void push(struct node **top, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Stack Overflow\n");
        return;
    }
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

// Pop function to remove and return the top element from the stack
int pop(struct node **top) {
    if (*top == NULL) {
        printf("Stack Underflow\n");
        return -1; // Indicate underflow
    }
    struct node *temp = *top;
    int poppedData = temp->data;
    *top = temp->next;
    free(temp);
    return poppedData;
}

// Function to print the entire stack
void printStack(struct node *top) {
    if (top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack contents: ");
    while (top != NULL) {
        printf("%d ", top->data);
        top = top->next;
    }
    printf("\n");
}

int main() {
    struct node *stack = NULL; // Initialize an empty stack
    int input;

    printf("Enter numbers to push onto the stack. Enter a non-natural number to print the stack and exit:\n");
    while (1) {
        printf("Input: ");
        if (scanf("%d", &input) != 1 || input <= 0) {
            // If non-natural number is entered, print stack and exit
            printStack(stack);
            break;
        }
        push(&stack, input);
    }

    // Cleanup: Free remaining nodes
    while (stack != NULL) {
        pop(&stack);
    }

    return 0;
}

