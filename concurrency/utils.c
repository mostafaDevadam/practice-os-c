#include <stdio.h>
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

pthread_mutex_t printMutex = PTHREAD_MUTEX_INITIALIZER;

void initRandom(void){
  srand((unsigned int)time(NULL));
}

void randomSleep(int maxSeconds){
   sleep(rand() % maxSeconds + 1);
}

void safePrint(const char *message){
    pthread_mutex_lock(&printMutex);
    printf("%s\n", message);
    pthread_mutex_unlock(&printMutex);
}

void destroyUtils(void){
    pthread_mutex_destroy(&printMutex);
}
