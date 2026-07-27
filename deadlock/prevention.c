#include <stdio.h>
#include "prevention.h"


static int lastResourceRequested[MAX_PROCESS];

void initializePrevention(SystemState *sys){
   (void)sys; // unused
   for(int i = 0; i < MAX_PROCESS; i++){
    lastResourceRequested[i] = -1;
   }
}

int preventRequest(SystemState *sys, int process, int request[]){
  (void)sys; // unused

  for(int r = 0; r < MAX_PROCESS; r++){
      if(request[r] > 0){
        if(r < lastResourceRequested[process]){
            printf("Request denied.\n");
            printf("Deadlock prevention: resource must be requested in increasing order.\n");
            return 0;
        }

        lastResourceRequested[process] = r;
      }
  }

  printf("Request satisfies prevention policy.\n");
  return 1;

}

void resetProcessOrder(int process){
    if(process >= 0 && process < MAX_PROCESS){
        lastResourceRequested[process] = -1;
    }

}