#include <stdio.h>
#include "m_queue.h"


void initQueue(Queue *q){
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

int isEmpty(Queue *q){
   return (q->size == 0);
}

int isFull(Queue *q){
   return (q->size == MAX_QUEUE);
}

void enqueue(Queue *q, M_PCB *process){

    if(isFull(q)){
        printf("Queue Overflow!\n");
        return;
    }

    
    q->rear = (q->rear +1) % MAX_QUEUE;
    q->items[q->rear] = process;
    q->size++;

    printf("enqueue: rear=%d front=%d size=%d ptr=%p pid=%d\n",
       q->rear,
       q->front,
       q->size,
       (void *)process,
       process->pid);

}


M_PCB *dequeue(Queue *q){

    if(isEmpty(q)){
        return NULL;
    }

    M_PCB *process = q->items[q->front];

    q->front = (q->front + 1) % MAX_QUEUE;
    q->size--;

    printf("dequeue: front=%d rear=%d size=%d ptr=%p\n",
       q->front,
       q->rear,
       q->size,
       (void *)q->items[q->front]);

    return process;

}

M_PCB *peek(Queue *q){
    if(isEmpty(q)){
        return NULL;
    }

    return q->items[q->front];

}

void printQueue(Queue *q){

    if(isEmpty(q)){
        printf("Ready Queue: Empty\n");
        return;
    }

    printf("Ready Queue");

    int index = q->front;

    for(int i = 0; i < q->size; i++){
        printf("P%d ", q->items[index]->pid);
        index = (index +1) % MAX_QUEUE;
    }

    printf("\n");
    

}
