

#ifndef DISPLAY_H
#define DISPLAY_H

#include "banker.h"

void displaySystemState(SystemState *sys);
void displayAllocation(SystemState *sys);
void displayMaximum(SystemState *sys);
void displayNeed(SystemState *sys);
void displayAvailable(SystemState *sys);
#endif