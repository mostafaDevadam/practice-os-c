#include <stdio.h>
#include "m_pcb.h"

void m_printPCB(M_PCB p){

    printf("p: %d\n", p.pid);


    const char *stateNames[] = {
        "NEW",
        "READY",
        "RUNNING",
        "WAITING",
        "TERMINATED"
    };

    printf("------------------------\n");
    printf("PID            : %d\n", p.pid);
    printf("Arrival Time   : %d\n", p.arrivalTime);
    printf("Burst Time     : %d\n", p.burstTime);
    printf("Remaining Time : %d\n", p.remainingTime);
    printf("Priority       : %d\n", p.priority);
    printf("CPU ID         : %d\n", p.cpuID);
    printf("State          : %s\n", stateNames[p.state]);
    printf("Completion     : %d\n", p.completionTime);
    printf("Turnaround     : %d\n", p.turnaroundTime);
    printf("Waiting        : %d\n", p.waitingTime);
    printf("Response       : %d\n", p.responseTime);
    printf("------------------------\n");
}