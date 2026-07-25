#include <stdio.h>
#include "src/shell.h"
#include "scheduler/pcb.h"
#include "scheduler/fcfs.h"
#include "scheduler/scheduler.h"


int main() {
    printf("Hello, World!\n");

    
    /*
    // pcb
    PCB p1;
    initializePCB(&p1, 1, 0, 5, 1);
    p1.state = READY;
    printPCB(&p1);

    // fcfs
    PCB processes[] = {
        {1, 0, 5, 5, 1, 0, 0, {0}, NEW, -1, -1, -1, -1, -1, NULL},
        {2, 2, 3, 3, 2, 0, 0, {0}, NEW, -1, -1, -1, -1, -1, NULL},
        {3, 4, 2, 2, 3, 0, 0, {0}, NEW, -1, -1, -1, -1, -1, NULL},
        {4, 6, 4, 4, 4, 0, 0, {0}, NEW, -1, -1, -1, -1, -1, NULL}
        
    };
    int n = sizeof(processes) / sizeof(processes[0]);
    fcfs(processes, n);

    // sjf
    PCB processes_sjf[4];
    initializePCB(&processes_sjf[0], 1, 0, 8, 2);
    initializePCB(&processes_sjf[1], 2, 1, 4, 1);
    initializePCB(&processes_sjf[2], 3, 2, 9, 3);
    initializePCB(&processes_sjf[3], 4, 3, 5, 2);
    int n_ = 4;
    sjf(processes_sjf, n_);

    // srtf
    PCB processes_srtf[4];
    initializePCB(&processes_srtf[0], 1, 0, 8, 2);
    initializePCB(&processes_srtf[1], 2, 1, 4, 1);
    initializePCB(&processes_srtf[2], 3, 2, 9, 3);
    initializePCB(&processes_srtf[3], 4, 3, 5, 2);
    srtf(processes_srtf, 4);

    // priority
    PCB processes_pr[4];
    initializePCB(&processes_pr[0], 1, 0, 8, 2);
    initializePCB(&processes_pr[1], 2, 1, 4, 1);
    initializePCB(&processes_pr[2], 3, 2, 9, 3);
    initializePCB(&processes_pr[3], 4, 3, 5, 2);
    priorityScheduling(processes_pr, 4);

    // round robin
    PCB processes_rr[4];
    initializePCB(&processes_rr[0], 1, 0, 8, 2);
    initializePCB(&processes_rr[1], 2, 1, 4, 1);
    initializePCB(&processes_rr[2], 3, 2, 9, 3);
    initializePCB(&processes_rr[3], 4, 3, 5, 2);
    roundRobin(processes_rr, 4, 2);
    */

    int n, choice, quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    PCB processes[n];

    for(int i = 0; i < n; i++){
        int at, bt, priority;

        printf("\nProcess %d\n", i + 1);

        printf("Arrival Time:");
        scanf("%d", &at);

        printf("Burst Time:");
        scanf("%d", &bt);

        printf("Priority:");
        scanf("%d", &priority);

        initializePCB(&processes[i], i + 1, at, bt, priority);

        
    }

    do {

        printf("\n===================================================\n");
        printf("   CPU Scheduling Simulator   \n");
        printf("---------------------------------------------------\n");
        printf("1. First Come First Serve (FCFS)\n");
        printf("2. Shortest Job First (SJF)\n");
        printf("3. Shortest Remaining Time First (SRTF)\n");
        printf("4. Priority Scheduling\n");
        printf("5. Round Robin\n");
        printf("0. Exit\n");
        printf("---------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch(choice){
           
            case 1:
                 fcfs(processes, n);
                 break;

             case 2:
                 sjf(processes, n);
                 break;

             case 3:
                 srtf(processes, n);
                 break;

             case 4:
                 priorityScheduling(processes, n);
                 break;

             case 5:
                 printf("Enter Time Quantum: ");
                 scanf("%d", &quantum);
                 roundRobin(processes, n, quantum);
                 break;

             case 0:
                 printf("Goodbye!\n");
                 break;


            default:
              printf("Invalid choice. Please try again.\n");
        }

    }while(choice != 0);
 
 
    return 0;
}