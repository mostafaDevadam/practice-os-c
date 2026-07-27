

#ifndef M_SJF_H
#define M_SJF_H

#include "m_pcb.h"
#include "m_cpu.h"

void sjfSchedule(M_PCB processes[], int n, CPU cpus[], int cpuCount);

#endif