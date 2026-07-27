#include <stdio.h>
#include "m_cpu.h"

void initializeCPUs(CPU cpus[], int count) {
    for (int i = 0; i < count; i++) {
        cpus[i].id = i;
        cpus[i].process = NULL;
        cpus[i].busy = 0;
    }
}