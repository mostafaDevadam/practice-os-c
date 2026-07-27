#ifndef M_ROUND_ROBIN_H
#define M_ROUND_ROBIN_H

#include "m_pcb.h"
#include "m_cpu.h"

void roundRobinSchedule(M_PCB processes[], int n, CPU cpus[], int cpuCount, int quantum);

#endif