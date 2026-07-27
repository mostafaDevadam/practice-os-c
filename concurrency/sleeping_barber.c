 #include <stdio.h>
 #include <pthread.h>

 #include <unistd.h>
 #include "sleeping_barber.h"
 #include <semaphore.h>


 #define CHAIRS 3
 #define CUSTOMERS 10

 int waitingCustomers = 0;

  static pthread_mutex_t mutex;
 sem_t customers;
 sem_t barber;


void *barberThread(void *){
     while(1){
         sem_wait(&customers);

         pthread_mutex_lock(&mutex);

         waitingCustomers--;
         printf("Barber is cutting hair. Waiting customers: %d\n", waitingCustomers);

         pthread_mutex_unlock(&mutex);

         sleep(2);

         printf("Barber finished haircut.");

         sem_post(&barber);

     }

     return NULL;
}


void *customerThread(void *arg){
    int id = *(int *)arg;

    pthread_mutex_lock(&mutex);

    if(waitingCustomers < CHAIRS){
        waitingCustomers++;

        printf("Customer %d is waiting. Waiting customers: %d\n", id, waitingCustomers);

        pthread_mutex_unlock(&mutex);

        sem_post(&customers);
        sem_wait(&barber);

        printf("Customer %d is getting haircut and leaves.\n", id);

    } else {
        printf("Customer %d is leaves (no empty chair) \n", id);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}



 void sleepingBarber(void){

    pthread_t barberThreadId;
    pthread_t customerThreads[CUSTOMERS];

    int customIds[CUSTOMERS];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&customers, 0, 0);
    sem_init(&barber, 0, 1);

    pthread_create(&barberThreadId, NULL, barberThread, NULL);

    for(int i = 0; i < CUSTOMERS; i++){
        customIds[i] = i + 1;
        pthread_create(&customerThreads[i], NULL, customerThread, &customIds[i]);

        sleep(1);
    }

    for(int i = 0; i < CUSTOMERS; i++){
        pthread_join(customerThreads[i], NULL);
    }

    pthread_cancel(barberThreadId);
    pthread_join(barberThreadId, NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&customers);
    sem_destroy(&barber);

    printf("\nSleeping Barber simulation finished. \n");
     
 }

