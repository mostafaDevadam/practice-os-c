
#ifndef DETECTION_H
#define DETECTION_H

#include "banker.h"

int detectDeadlock(SystemState *sys, int deadlocked[]);

void printDeadlockProcesses(int deadlocked[], int count);

 #endif