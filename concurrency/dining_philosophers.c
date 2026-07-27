#include <stdio.h>
#include <pthread.h>
#include "dining_philosophers.h"
 #include <unistd.h>

 
#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];

void *philosopher(void *arg){
     int id = *(int *)arg;
     int leftFork = id;
     int rightFork = (id + 1) % NUM_PHILOSOPHERS;

     for(int i = 0; i < 3; i++){
         printf("Philosopher %d is thinking...\n", id);
         sleep(1);

         if(id % 2 == 0){
           pthread_mutex_lock(&forks[leftFork]);
           printf("Philosopher %d picked up left fork \n", id);

           pthread_mutex_lock(&forks[rightFork]);
           printf("Philosopher %d picked up right fork \n", id);

         }else {

            pthread_mutex_lock(&forks[rightFork]);
            printf("Philosopher %d picked up right fork \n", id);

            pthread_mutex_lock(&forks[leftFork]);
            printf("Philosopher %d picked up left fork \n", id);

         }

         printf("Philosopher %d is eating...\n", id);
         sleep(1);

         pthread_mutex_unlock(&forks[leftFork]);
         pthread_mutex_unlock(&forks[rightFork]);

         printf("Philosopher %d released both forks \n", id);
     }

     return NULL;
}


void diningPhilosophers(void){

    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    for(int i=0; i < NUM_PHILOSOPHERS; i++){
        pthread_mutex_init(&forks[i], NULL);
    }

    for(int i = 0; i < NUM_PHILOSOPHERS; i++){
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for(int i = 0; i < NUM_PHILOSOPHERS; i++){
        pthread_join(philosophers[i], NULL);
    }

    for(int i = 0; i < NUM_PHILOSOPHERS; i++){
        pthread_mutex_destroy(&forks[i]);
    }

    printf("\nDining Philosophers simulation finished.\n");



}

