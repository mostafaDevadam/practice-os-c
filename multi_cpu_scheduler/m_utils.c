

#include <stdio.h>
#include "m_cpu.h"



void printLine(void){
    printf("------------------------------------------------------------\n");
}


void printProcessTable(M_PCB processes[], int n){

    printLine();

    printf(
        "%-5s %-5s %-5s %-5s %-8s %-5s\n",
        "PID",
        "AT",
        "BT",
        "PRI",
        "STATE",
        "CPU"
    );

    printLine();

    for(int i = 0; i < n; i++){

        const char *state;

        switch(processes[i].state){

            case NEW:
                 state = "NEW";
                 break;

              case READY:
                 state = "READY";
                 break;

              case RUNNING:
                 state = "RUNNING";
                 break;

              case WAITING:
                 state = "WAIT";
                 break;

              case TERMINATED:
                 state = "TERM";
                 break;

            

              default:
                     state = "UNK";
        }


        printf(
            "%-5d %-5d %-5d %-5d %-8s %-5d\n",
            processes[i].pid,
            processes[i].arrivalTime,
            processes[i].burstTime,
            processes[i].priority,
            state,
            processes[i].cpuID

        );

    }



    printLine();


  
}


void printCPUStatus(CPU cpus[], int cpuCount){

    printLine();

    printf("CPU STATUS\n");

    printLine();

    for(int i = 0; i < cpuCount; i++){
        if(cpus[i].busy){
            printf("CPU %d : Running P%d\n", cpus[i].id, cpus[i].process->pid);

        } else {
            printf("CPU %d : IDLE\n", cpus[i].id);
        }
    }

    printLine();

}


char *get_state(M_PCB process){
    
    switch(process.state){
        case NEW:
            return "NEW";

        case READY:
            return "READY";

        case RUNNING:
            return "RUNNING";

        case WAITING:
            return "WAIT";

        case TERMINATED:
            return "TERM";

        default:
            return "UNK";
        }

        
}

