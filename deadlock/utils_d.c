 #include <stdio.h>
 #include "utils_d.h"



void printMatrix_d(const char *title, 
    int matrix[MAX_PROCESS][MAX_RESOURCE], 
    int rows, 
    int cols){

        printf("\n%s\n", title);

        for(int i = 0; i < rows; i++){
            printf("P%d\t", i);

            for(int j = 0; i < cols; j++){
                printf("%d ", matrix[i][j]);
            }

            printf("\n");
        }
     
}


 void printVector_d(const char *title, int vector[MAX_RESOURCE], int size){
     printf("\n%s\n", title);

     for(int i=0; i < size; i++){
         printf("%d ", vector[i]);
     }
     printf("\n");
 }


 void printSafeSequence_d(int safeSequence[], int count){
      printf("\nSafe Sequence\n");

      for(int i =0; i < count; i++){
          printf("%d ", safeSequence[i]);

          if(i != count - 1){
              printf(" -> ");
          }
      }
      printf("\n");
 }




 void releaseResources_d(SystemState *sys, int process){

     if(process < 0 || process >= sys->processes) {
        printf("Invalid process number.\n");
        return;
     }

     for(int i = 0; i < sys->resources; i++){
         sys->available[i] += sys->allocation[process][i];
         sys->allocation[process][i] = 0;
         sys->need[process][i] = sys->maximum[process][i];
     }

     printf("Resources released from P%d.\n", process);

 }
