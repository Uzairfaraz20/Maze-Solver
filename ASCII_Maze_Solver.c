#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool debugOn = false;

typedef struct mazeStruct {
    char arr[32][32]; /* allows for a maze of size 30x30 plus outer walls */
    int xsize, ysize;
    int xstart, ystart;
    int xend, yend;
} maze;

struct Stack {
    char* array;
    int top;
    int size;
};

struct Stack* initializeStack(int size)
{
    if(debugOn == true) {
        printf("Initializing Stack of size %d \n", size);
    }
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->size = size;
    stack->top = -1;
    stack->array = (char*)malloc(stack->size * sizeof(char));
    return stack;
}

bool isFull(struct Stack* stack)
{
    if(debugOn == true) {
        printf("Checking if Stack is full \n");
    }
    return (stack->top == stack->size - 1);
}

bool isEmpty(struct Stack* stack)
{
    if(debugOn == true) {
        printf("Checking if Stack is empty \n");
    }
    return (stack->top == -1);
}

void resetStack(struct Stack* stack)
{
    if(debugOn == true) {
        printf("Resetting Stack to size: 2 \n");
    }
    stack->size = 2;
    stack->array = (char*)malloc(stack->size * sizeof(char));
    stack->top = -1;
}

void push(struct Stack* stack, char item)
{
    if(debugOn == true) {
        printf("Pushing Symbol onto stack \n");
    }
    if(isFull(stack) == true) {
        if(debugOn == true) {
            printf("Stack is Full, Allocating space \n");
        }
        char* temp;
        temp = (char*)malloc((stack->size + 2) * sizeof(char));
        int i;
        for(i = 0; i < stack->size; i++) {
            temp[i] = stack->array[i];
        }
        free(stack->array);
        (stack->array) = temp;
        stack->size += 2;
        if(debugOn == true) {
            printf("%d values copied \n", stack->size);
            printf("Array size changed from %d to %d \n", stack->size - 2, stack->size);
        }
    } else if(isEmpty(stack) == true) {
        resetStack(stack);
    }
    stack->array[++stack->top] = item;
    return;
}

void pop(struct Stack* stack)
{
    if(debugOn == true) {
        printf("Popping Stack \n");
    }
    if(isEmpty(stack)) {
        if(debugOn == true) {
            printf("Nothing to pop. Stack is empty \n");
        }
    }
    char* temp;
    temp = (char*)malloc((stack->top - 1) * sizeof(char));
    int i;
    for(i = 0; i < stack->top; i++) {
        temp[i] = stack->array[i];
    }
    free(stack->array);
    (stack->array) = temp;
    stack->top -= 1;
}
char getTop(struct Stack* stack)
{
    if(debugOn == true) {
        printf("Getting Top at %d: \n", stack->top);
    }

    return stack->array[stack->top];
}

void printInfo(char* keeper, int pos)
{
    printf("%s", keeper);

    int k;
    for(k = 0; k < pos; k++) {
        printf(" ");
    }
    printf("^ ");
}

int main(int argc, char** argv)
{
    maze m1;

    int xpos, ypos;
    int i, j;

    FILE* src;

    /* verify the proper number of command line arguments were given */
    if(argc != 2) {

        printf("Usage: %s <input file name>\n", argv[0]);
        exit(-1);
    }

    /* Try to open the input file. */
    if((src = fopen(argv[1], "r")) == NULL) {
        printf("Can't open input file: %s", argv[1]);
        exit(-1);
    }

    /* read in the size, starting and ending positions in the maze */
    fscanf(src, "%d %d", &m1.xsize, &m1.ysize);
    fscanf(src, "%d %d", &m1.xstart, &m1.ystart);
    fscanf(src, "%d %d", &m1.xend, &m1.yend);
    /* print them out to verify the input */
    printf("size: %d, %d\n", m1.xsize, m1.ysize);
    printf("start: %d, %d\n", m1.xstart, m1.ystart);
    printf("end: %d, %d\n", m1.xend, m1.yend);

    /* initialize the maze to empty */
    for(i = 0; i < m1.xsize + 2; i++)
        for(j = 0; j < m1.ysize + 2; j++)
            m1.arr[i][j] = '.';

    /* mark the borders of the maze with *'s */
    for(i = 0; i < m1.xsize + 2; i++) {
        m1.arr[i][0] = '*';
        m1.arr[i][m1.ysize + 1] = '*';
    }
    for(i = 0; i < m1.ysize + 2; i++) {
        m1.arr[0][i] = '*';
        m1.arr[m1.xsize + 1][i] = '*';
    }

    /* mark the starting and ending positions in the maze */
    m1.arr[m1.xstart][m1.ystart] = 's';
    m1.arr[m1.xend][m1.yend] = 'e';

    /* mark the blocked positions in the maze with *'s */
    while(fscanf(src, "%d %d", &xpos, &ypos) != EOF) {
        m1.arr[xpos][ypos] = '*';
    }

    /* print out the initial maze */
    for(i = 0; i < m1.xsize + 2; i++) {
        for(j = 0; j < m1.ysize + 2; j++)
            printf("%c", m1.arr[i][j]);
        printf("\n");
    }
}

