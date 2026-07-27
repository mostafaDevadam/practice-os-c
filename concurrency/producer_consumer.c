 #include <stdio.h>
 #include "producer_consumer.h"
 #include <semaphore.h>
 #include <pthread.h>
 #include <unistd.h>

 #define BUFFER_SIZE 10
 #define PRODUCERS 2
 #define CONSUMERS 2
 #define ITEMS_PER_PRODUCER 10

 int buffer[BUFFER_SIZE];
 int in = 0;
 int out = 0;
 
 static pthread_mutex_t mutex;
 sem_t empty;
 sem_t full;

 void *producer(void *arg){
    int id = *(int *)arg;

    for(int i=0; i <= ITEMS_PER_PRODUCER; i++){
        int item = id * 100 + i;

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer %d produced %d at %d \n", id, item, in);

        in = (in + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }

    return NULL;
 }

 void *consumer(void *arg){
    int id = *(int *)arg;

    int totalItems = (PRODUCERS * ITEMS_PER_PRODUCER) / CONSUMERS;

    for(int i = 0; i < totalItems; i++){
        sem_wait(&full);
        pthread_mutex_lock(&mutex); 

        int item = buffer[out];
        printf("Consumer %d consumed %d from %d \n", id, item, out);

        out = (out + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(1);
    }
    return NULL;
 }
 void producerConsumer(void){
   pthread_t producers[PRODUCERS];
   pthread_t consumers[CONSUMERS];

   int producerIds[PRODUCERS];
   int consumerIds[CONSUMERS];

   pthread_mutex_init(&mutex, NULL);
   
   sem_init(&empty, 0, BUFFER_SIZE);
   sem_init(&full, 0, 0);

   for(int i = 0; i < PRODUCERS; i++){
       producerIds[i] = i;
       pthread_create(&producers[i], NULL, producer, &producerIds[i]);
   }

   for(int i = 0; i < CONSUMERS; i++){
       consumerIds[i] = i + 1;
       pthread_create(&consumers[i], NULL, consumer, &consumerIds[i]);
   }

   for(int i = 0; i < PRODUCERS; i++){
       pthread_join(producers[i], NULL);
   }

   for(int i = 0; i < CONSUMERS; i++){
       pthread_join(consumers[i], NULL);
   }

   pthread_mutex_destroy(&mutex);
   sem_destroy(&empty);
   sem_destroy(&full);

   printf("\nProducer Consumer simulation finished\n");
 }