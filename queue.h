#include <stdlib.h>
#include <stdio.h>
 
typedef struct QNode
{
    int key;
    struct QNode *next;
} QNode;

typedef struct queue
{
    struct QNode *front, *rear;
    int size;
} queue;
 
QNode* new_node(int k);
 
queue *create_queue();
 
void enqueue(queue *q, int k);
 
QNode *dequeue(queue *q);