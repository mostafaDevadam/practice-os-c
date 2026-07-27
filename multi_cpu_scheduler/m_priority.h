#ifndef M_PRIORITY_H
#define M_PRIORITY_H

#include "m_pcb.h"
#include "m_cpu.h"

void prioritySchedule(M_PCB processes[], int n, CPU cpus[], int cpuCount);


#endif