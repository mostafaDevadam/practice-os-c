
#include <stdio.h>
#include "display.h"

void displaySystemState(SystemState *sys){
    printf("\n============ System State=======\n");

    displayAllocation(sys);
    displayMaximum(sys);
    displayNeed(sys);
    displayAvailable(sys);

    printf("==============================\n");

}


void displayAllocation(SystemState *sys){

    printf("\nAllocation Matrix:\n");

    for(int i = 0; i < sys->processes; i++){
        printf("P%d\t", i);

        for(int j = 0; j < sys->resources; j++){
            printf("%d ", sys->allocation[i][j]);
        }

        printf("\n");
    }

}


void displayMaximum(SystemState *sys){

    printf("\nMaximum Matrix:\n");

    for(int i = 0; i < sys->processes; i++){
        printf("P%d\t", i);

        for(int j = 0; j < sys->resources; j++){
            printf("%d ", sys->maximum[i][j]);
        }

        printf("\n");
    }

}


void displayNeed(SystemState *sys){

    printf("\nNeed Matrix: \n");

    for(int i = 0; i < sys->processes; i++){
        printf("P%d\t", i); 

        for(int j = 0; j < sys->resources; j++){
            printf("%d ", sys->need[i][j]);
        }

        printf("\n");
    }

}


void displayAvailable(SystemState *sys){

    printf("\nAvailable Matrix:\n");

    for(int i = 0; i < sys->resources; i++){
        printf("R%d ", i);
        printf("%d\n", sys->available[i]);
    }
    printf("\n");

}





