 
#ifndef UTILS_H
#define UTILS_H
 
 #include "banker.h"

 void printMatrix_d(const char *title, int matrix[MAX_PROCESS][MAX_RESOURCE], int rows, int cols);

 void printVector_d(const char *title, int vector[MAX_RESOURCE], int size);

 void printSafeSequence_d(int safeSequence[], int count);

 void releaseResources_d(SystemState *sys, int process);

 #endif