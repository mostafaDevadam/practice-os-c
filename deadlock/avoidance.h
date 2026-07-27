
#ifndef AVOIDANCE_H
#define AVOIDANCE_H


#include "banker.h"

int avoidDeadlock(SystemState *sys, int safeSequence[]);
 
int avoidRequest(SystemState *sys, int process, int request[]);

#endif