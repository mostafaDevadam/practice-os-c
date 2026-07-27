 #include <stdio.h>
 #include "detection.h"


 int detectDeadlock(SystemState *sys, int deadlocked[]){

    int work[MAX_RESOURCE];
    int finish[MAX_PROCESS];

    for(int i = 0; i < sys->processes; i++){
        work[i] = sys->available[i];
    }

    for(int i = 0; i < sys->processes; i++){
       int allocated = 0;

       for(int j = 0; j < sys->resources; j++){
          if(sys->allocation[i][j] != 0){
              allocated = 1;
              break;
          }
       }

       finish[i] = !allocated;
    }

    int changed;

    do{
        changed = 0;

        for(int i = 0; i < sys->processes; i++){
            if(!finish[i]){

                int j;

                for(j =0; j < sys->resources; j++){
                    if(sys->need[i][j] > work[j]){
                        break;
                    }
                }

                if(j == sys->resources){
                    
                    for(int k = 0; k < sys->resources; k++){
                        work[k] += sys->allocation[i][k];
                    }

                    finish[i] = 1;
                    changed = 1;
                }
                
            }
        }

    }while(changed);


    int count = 0;

    for(int i = 0; i < sys->processes; i++){
        if(!finish[i]){
            deadlocked[count++] = i;
            
        }
    }

    return count;

 }



void printDeadlockProcesses(int deadlocked[], int count){

    if(count == 0){
        printf("No deadlock detected.\n");
        return;
    }

    printf("Deadlocked detected.\n");
    printf("Deadlocked Processes: ");

    for(int i = 0; i < count; i++){
        printf("P%d ", deadlocked[i]);
    }

    printf("\n");

}

