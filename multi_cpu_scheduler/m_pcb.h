#ifndef M_PBC_H
#define M_PBC_H

#include "../scheduler/pcb.h"




typedef struct {
   int pid;

   int arrivalTime;
   int burstTime;  
   int remainingTime;

   int priority;

  

   //int start_time;

   int completionTime;
   int turnaroundTime;
   int waitingTime;
   int responseTime;

   

   ProcessState state;

   int cpuID;


} M_PCB;

void m_printPCB(M_PCB p);

#endif