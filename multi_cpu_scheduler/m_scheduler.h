#ifndef M_SCHEDULER_H
#define M_SCHEDULER_H

#include "m_pcb.h"
#include "m_cpu.h"

void schedule(M_PCB processes[], int n, CPU cpus[], int cpuCount);


#endif