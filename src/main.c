#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../helpers/linked_list.h"

#define BUFFSIZE 1024

int prec(char c) {
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

char associativity(char c) {
    if (c == '^')
        return 'R';
    return 'L'; 
}

void removeChar(char *input, char c) {
    int i = 0, j = 0;

    while (input[i]) {
        if (input[i] != c) {
            input[j++] = input[i];
        }
        i++;
    }
    
    input[j]=0;
}

void tokenize(char* input, char* tokens) {
    int iIndex = 0, tIndex = 0, shouldAddSpace = 0;
    while (input[iIndex]) {
        if (isdigit(input[iIndex]) || (input[iIndex] == '.')) {
            tokens[tIndex] = input[iIndex];
            tIndex += 1;
            shouldAddSpace = 1;
        } else {
            if (shouldAddSpace == 1) {
                tokens[tIndex] = ' ';
                tIndex += 1;
            }
            tokens[tIndex] = input[iIndex];
            tIndex += 1;
            tokens[tIndex] = ' ';
            tIndex += 1;
        }
        iIndex += 1;
    }
}

void getOperations(char* tokens, char* operations) {
    char stack[SIZE];
    int len = strlen(operations);
    int resultIndex = 0, stackIndex = -1;
    for (int i = 0; i < len; i++) {
        char c = operations[i];
 
        // If the scanned character is an operand, add it to the output string.
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
            operations[resultIndex++] = c;
        }
        // If the scanned character is an ‘(‘, push it to the stack.
        else if (c == '(') {
            stack[++stackIndex] = c;
        }
        // If the scanned character is an ‘)’, pop and add to the output string from the stack
        // until an ‘(‘ is encountered.
        else if (c == ')') {
            while (stackIndex >= 0 && stack[stackIndex] != '(') {
                operations[resultIndex++] = stack[stackIndex--];
            }
            stackIndex--; // Pop '('
        }
        // If an operator is scanned
        else {
            while (stackIndex >= 0 && (prec(operations[i]) < prec(stack[stackIndex]) ||
                                       prec(operations[i]) == prec(stack[stackIndex]) &&
                                           associativity(operations[i]) == 'L')) {
                operations[resultIndex++] = stack[stackIndex--];
            }
            stack[++stackIndex] = c;
        }
    }
 
    // Pop all the remaining elements from the stack
    while (stackIndex >= 0) {
        operations[resultIndex++] = stack[stackIndex--];
    }

    operations[resultIndex] = "\0";
}

int main(int argc, char* argv[]) {
    printf("Write a task to solve (note: length of input cannot exceed %i): ", BUFFSIZE);

    char* input = malloc(BUFFSIZE);
    if (NULL == input) {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    fgets(input, BUFFSIZE, stdin);
    if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n')) {
        input[strlen(input) - 1] = '\0';
    }

    removeChar(input, ' ');

    char* tokens = malloc(BUFFSIZE);
    if (NULL == tokens) {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    tokenize(input, tokens);
    // free(input);

    char* operations = malloc(BUFFSIZE);
    if (NULL == operations) {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    getOperations(input, operations);
    free(tokens);

    printf("%s", operations);

    return 0;
}