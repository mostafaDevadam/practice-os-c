

#include <stdio.h>
#include <stdlib.h>

#include "m_input.h"


int loadProcesses(const char *filename, M_PCB processes[], int *cpuCount){

    FILE *fp = fopen(filename, "r");

    if(fp == NULL){
        printf("Error: Cannot open %s\n", filename);
        return -1;
    }

    int n;

    if(fscanf(fp, "%d", cpuCount) != 1){
        fclose(fp);
        return -1;
    }


    if(fscanf(fp. "%d", &n) != 1){
        fclose(fp);
        return -1;
    }

    for(int i =0; i < n; i++){
        fscanf(fp, 
            "%d %d %d %d",
            &processes[i].pid,
            &processes[i].arrivalTime,
             &processes[i].burstTime,
             &processes[i].priority
        
        );

        processes[i].remainingTime = processes[i].burstTime;

        processes[i].completionTime = 0;
        processes[i].turnaroundTime = 0;
        processes[i].waitingTime = 0;
        processes[i].responseTime = -1;

        processes[i].state = READY;
        processes[i].cpuID = -1;

    }

    fclose(fp);

    return n;

}
