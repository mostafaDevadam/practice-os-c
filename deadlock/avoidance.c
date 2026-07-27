#include <stdio.h>
#include "avoidance.h"


int avoidDeadlock(SystemState *sys, int safeSequence[]){
    return isSafeState(sys, safeSequence);

}
 
int avoidRequest(SystemState *sys, int process, int request[]){
   return requestResources(sys, process, request);
}