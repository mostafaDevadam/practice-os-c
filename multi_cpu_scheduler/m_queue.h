#ifndef M_QUEUE_H
#define M_QUEUE_H

#include "m_pcb.h"

#define MAX_QUEUE 100

typedef struct {
  M_PCB *items[MAX_QUEUE];
  int front;
  int rear;
  int size;
} Queue;


void initQueue(Queue *q);
int isEmpty(Queue *q);
int isFull(Queue *q);
void enqueue(Queue *q, M_PCB *process);
M_PCB *dequeue(Queue *q);
M_PCB *peek(Queue *q);
void printQueue(Queue *q);

#endif