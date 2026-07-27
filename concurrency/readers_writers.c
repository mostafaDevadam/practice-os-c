 #include <stdio.h>
 #include <pthread.h>
 #include "readers_writers.h"
 #include <unistd.h>

 #define NUM_READERS 5
 #define NUM_WRITERS 5

 int sharedData = 0;
 int readCount = 0;

  static pthread_mutex_t mutex;
  static pthread_mutex_t writeLock;

void *reader(void *arg){
   int id = *(int *)arg;

   for(int i = 0; i < 3; i++){
       
    // Entry Section
    pthread_mutex_lock(&mutex);
    readCount++;
    if(readCount == 1){
        pthread_mutex_lock(&mutex);
    }
    pthread_mutex_unlock(&mutex);


    // Critical Section
    printf("Reader %d reads value = %d\n", id, sharedData);
    sleep(1);

    // Exit Section
    pthread_mutex_lock(&mutex);
    readCount--;

    if(readCount == 0){
        pthread_mutex_unlock(&writeLock);
    }

    pthread_mutex_unlock(&mutex);

    sleep(1);


   }

   return NULL;
}

void *writer(void *arg){

    int id = *(int *)arg;

    for(int i = 0; i < 3; i++){
         pthread_mutex_lock(&writeLock);

         sharedData++;
         printf("Writer %d writes value = %d\n", id, sharedData);

         sleep(2);

         pthread_mutex_unlock(&writeLock);

         sleep(1);
    }

    return NULL;

}


void readersWriters(void){
     pthread_t readers[NUM_READERS], writers[NUM_WRITERS];

     int readersIds[NUM_READERS];
     int writersIds[NUM_WRITERS];

     pthread_mutex_init(&mutex, NULL);
     pthread_mutex_init(&writeLock, NULL);

     // create reader threads
     for(int i = 0; i < NUM_READERS; i++){
         readersIds[i] = i + 1;
         pthread_create(&readers[i], NULL, reader, &readersIds[i]);
     }

     // create writer threads
     for(int i = 0; i < NUM_WRITERS; i++){
         writersIds[i] = i + 1;
         pthread_create(&writers[i], NULL, writer, &writersIds[i]);
     }

     // wait for readers
     for(int i = 0; i < NUM_READERS; i++){
         pthread_join(readers[i], NULL);
     }




     // wait for writers
     for(int i = 0; i < NUM_WRITERS; i++){
         pthread_join(writers[i], NULL);
     }

     pthread_mutex_destroy(&mutex);
     pthread_mutex_destroy(&writeLock);

     printf("\nReaders-Writers simulation finished.\n");




}

