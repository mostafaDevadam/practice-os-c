
#ifndef M_CPU_H
#define M_CPU_H

#include "m_pcb.h"

#define MAX_CPU 8

typedef struct {
    int id;
    M_PCB *process;
    int busy;
} CPU;

void initializeCPUs(CPU cpus[], int count);

#endif