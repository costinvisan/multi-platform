#include "queue.h"
QNode* new_node(int k)
{
    QNode *temp = (QNode*)malloc(sizeof(QNode));
    temp->key = k;
    temp->next = NULL;
    return temp; 
}

queue *create_queue()
{
    queue *q = (queue*)malloc(sizeof(queue));
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

void enqueue(queue *q, int k)
{
    QNode *temp = new_node(k);
    q->size++;
    
    if (q->rear == NULL)
    {
       q->front = q->rear = temp;
       return;
    }
 
    q->rear->next = temp;
    q->rear = temp;
}

QNode *dequeue(queue *q)
{
    if (q->front == NULL)
       return NULL;
 
    QNode *temp = q->front;
    q->front = q->front->next;
 
    if (q->front == NULL)
       q->rear = NULL;
    
    q->size--;

    return temp;
}
