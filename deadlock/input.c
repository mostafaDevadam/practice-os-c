 #include <stdio.h>
 #include "input.h"

 void inputSystemState(SystemState *sys){

     printf("Enter number of processes (max %d): ", MAX_PROCESS);
     scanf("%d", &sys->processes);

     printf("Enter number of resource types (max %d):", MAX_RESOURCE);
     scanf("%d", &sys->resources);

     printf("\nEnter Allocation Matrix:\n");
     for(int i =0; i < sys->processes; i++){
         printf("Process P%d:\n", i);
         for(int j = 0; j < sys->resources; j++){
             printf("Allocation[%d][%d] ", i, j);
             scanf("%d", &sys->allocation[i][j]);
         }
     }

     printf("\nEnter Maximum Matrix:\n");
     for(int i =0; i < sys->processes; i++){
         printf("Process P%d:\n", i);
         for(int j = 0; j < sys->resources; j++){
             printf("Maximum[%d][%d] ", i, j);
             scanf("%d", &sys->maximum[i][j]);
         }
     }

     printf("\nEnter Available Resources:\n");
     for(int i =0; i < sys->resources; i++){
         printf("Available[%d] ", i);
         scanf("%d", &sys->available[i]);
     }

        printf("Processes = %d\n", sys->processes);
        printf("Resources = %d\n", sys->resources);
        //fflush(stdout);

     calculateNeed(sys);

     printf("\n System data loaded successfully.\n");


 }