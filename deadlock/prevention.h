

#ifndef PREVENTION_H
#define PREVENTION_H


#include "banker.h"

void initializePrevention(SystemState *sys);

int preventRequest(SystemState *sys, int process, int request[]);

void resetProcessOrder(int process);

 #endif