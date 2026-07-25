#include <stdio.h>
#include "pcb.h"
#include "scheduler.h"
#include "gantt.h"


void roundRobin(PCB processes[], int n, int quantum){

    int queue[100];
    int front = 0, rear = 0;

    

    int currentTime = 0;
    int completed = 0;
    int visited[100] = {0};
    int prev = -1;

    int start = currentTime;

    printf("\n ====== Round Robin ======= ");
    printf("Time Quantum = %d\n", quantum);
    printf("\nGantt Chart\n|");

    for(int i=0; i < n; i++ ){
        if(processes[i].arrival_time == 0){
            queue[rear++] = i;
            visited[i] = 1;
        }
    }
    while(completed < n){

        if(front == rear){
            currentTime++;

            for(int i = 0; i < n; i++){
                if(!visited[i] && processes[i].arrival_time <= currentTime){
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }

            continue;
        }

        int index = queue[front++];

        if(prev != index){
            printf(" P%d |", processes[index].pid);
            prev = index;
        }

        if(processes[index].response_time == -1){
            processes[index].start_time = currentTime;
            processes[index].response_time = currentTime - processes[index].arrival_time;
        }

        processes[index].state = RUNNING;

        int execute = (processes[index].remaining_time <= quantum) ? processes[index].remaining_time : quantum;
    
       
        processes[index].remaining_time -= execute;
        currentTime += execute;

        // gantt
        addGanttEntry(processes[index].pid, start, currentTime);

        for(int i = 0; i < n; i++){
            if(!visited[i] && processes[i].arrival_time <= currentTime){
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if(processes[index].remaining_time > 0){
            processes[index].state = READY;
            queue[rear++] = index;
        }else {
            processes[index].state = TERMINATED;
            completed++;

            processes[index].completion_time = currentTime;
            processes[index].turnaround_time = currentTime - processes[index].arrival_time;
            processes[index].waiting_time = processes[index].turnaround_time - processes[index].burst_time;

        }


    
    }

    printf("\n\n");

    printf(
        "%-5s %-5s %-5s %-5s %-5s %-5s %-5s \n",
        "PID", "AT", "BT", "CT", "TT", "WT", "RT"
        
    );

    double totalWT, totalTT, totalRT = 0;

    for(int i = 0; i < n; i++){
        printf(
            "%-5d %-5d %-5d %-5d %-5d %-5d %-5d %-5d\n",
            processes[i].pid,
            processes[i].arrival_time,
            processes[i].burst_time,
            processes[i].start_time,
            processes[i].completion_time,
            processes[i].turnaround_time,
            processes[i].waiting_time,
            processes[i].response_time
        );

         totalWT += processes[i].waiting_time;
        totalTT += processes[i].turnaround_time;
        totalRT += processes[i].response_time;

    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f", totalTT / n);
    printf("\nAverage Response Time: %.2f", totalRT / n);

   


}