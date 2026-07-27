
#ifndef BANKER_H
#define BANKER_H


#define MAX_PROCESS 10
#define MAX_RESOURCE 10

typedef struct 
{
     int processes;
     int resources;

     int allocation[MAX_PROCESS][MAX_RESOURCE];
     int maximum[MAX_PROCESS][MAX_RESOURCE];
     int need[MAX_PROCESS][MAX_RESOURCE];
     int available[MAX_RESOURCE];


} SystemState;


void calculateNeed(SystemState *sys);

int isSafeState(SystemState *sys, int safeSequence[]);

int requestResources(SystemState *sys, int process, int request[]);

#endif