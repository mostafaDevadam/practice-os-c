 #include <stdio.h>
 #include "banker.h"

 void calculateNeed(SystemState *sys){
     for(int i =0; i < sys->processes; i++){
         for(int j = 0; j < sys->resources; j++){
             sys->need[i][j] = sys->maximum[i][j] - sys->allocation[i][j];
         }
     }

 }

int isSafeState(SystemState *sys, int safeSequence[]){

    int work[MAX_RESOURCE];
    int finish[MAX_PROCESS] = {0};

    for(int i = 0; i < sys->resources; i++){
        work[i] = sys->available[i];
    }

    int count = 0;

    while(count < sys->processes){

        int found = 0;

        for(int i = 0; i < sys->processes; i++){
            if(!finish[i]){
                int j;

                for(j = 0; j < sys->resources; j++){
                    if(sys->need[i][j] > work[j]){
                        break;
                    }
                }

                if(j == sys->resources){
                    for(int k = 0; k < sys->resources; k++){
                        work[k] += sys->allocation[i][k];
                    }

                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(!found){
            return 0;
        }

    }



    return 1;



}

int requestResources(SystemState *sys, int process, int request[]){

    for(int i =0; i < sys->resources; i++){
        if(request[i] > sys->need[process][i]){
            printf("Error: Request exceeds process need.\n");
            return 0;
        }
    }

    for(int i =0; i < sys->resources; i++){
        if(request[i] > sys->available[i]){
            printf("Resource are not available.\n");
            return 0;
        }
    }

    for(int i =0; i < sys->resources; i++){
        sys->available[i] -= request[i];
        sys->allocation[process][i] += request[i];
        sys->need[process][i] -= request[i];
    }

    int safeSequence[MAX_PROCESS];

    if(isSafeState(sys, safeSequence)){
        printf("Request granted.\n");
        return 1;
    }

    for(int i =0; i < sys->resources; i++){
        sys->available[i] += request[i];
        sys->allocation[process][i] -= request[i];
        sys->need[process][i] += request[i];
    }

    printf("Request denied. System would become unsafe.\n");
    return 0;




}