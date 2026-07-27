#ifndef M_UTILS_H
#define M_UTILS_H

#include "m_pcb.h"
#include "m_cpu.h"

void printLine(void);
void printProcessTable(M_PCB processes[], int n);
void printCPUStatus(CPU cpus[], int cpuCount);
char *get_state(M_PCB process);

#endif