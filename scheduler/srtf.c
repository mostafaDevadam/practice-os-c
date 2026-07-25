#include <stdio.h>
#include "pcb.h"
#include "scheduler.h"

void srtf(PCB processes[], int n){

    int completed = 0;
    int currentTime = 0;
    int prev = -1;

    printf("\n ======== SRTF Scheduling ========= \n");
    printf("\nGantt Chart\n");



    while(completed < n) {
            int index = -1;
            int shortest = 999999;


            for(int i = 0; i < n; i++){
            if(processes[i].arrival_time <= currentTime && 
                processes[i].remaining_time > 0 &&
                processes[i].remaining_time < shortest)
                {
                    shortest = processes[i].remaining_time;
                    index = i;
                }
            }

            if(index == -1){
                currentTime++;
                continue;
            }

            if(prev != index){
                printf(" p%d | ", processes[index].pid);
                prev = index;
            }

            if(processes[index].response_time == -1){
                processes[index].start_time = currentTime;
                processes[index].response_time = currentTime - processes[index].arrival_time;
            }

            processes[index].state = RUNNING;

            processes[index].remaining_time--;
            currentTime++;

            if(processes[index].remaining_time == 0){
                completed++;

                processes[index].completion_time = currentTime;
                processes[index].turnaround_time = currentTime - processes[index].arrival_time;

                processes[index].waiting_time = processes[index].turnaround_time - processes[index].burst_time;

                processes[index].state = TERMINATED;
            }

    }

    printf("\n\n");
    printf("%-5s %-5s %-5s %-5s %-5s %-5s %-5s \n", "PID", "AT", "BT", "CT", "TAT", "WT", "RT");

    double totalWT, totalTAT, totalRT = 0;

    for(int i = 0; i < n; i++){

        printf(
            "%-5d %-5d %-5d %-5d %-5d %-5d %-5d \n",
            processes[i].pid,
            processes[i].arrival_time,
            processes[i].burst_time,
            processes[i].completion_time,
            processes[i].turnaround_time,
            processes[i].waiting_time,
            processes[i].response_time

        );
        totalWT += processes[i].waiting_time;
        totalTAT += processes[i].turnaround_time;
        totalRT += processes[i].response_time;


    }


    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
    printf("Aberage Response Time: %.2f\n", totalRT / n);
}

