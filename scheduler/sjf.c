#include <stdio.h>
#include "pcb.h"
#include "sjf.h"

void sjf(PCB processes[], int n){

    int completed = 0, currentTime = 0;
    
    int visited[n];

    for(int i = 0; i < n; i++){
        visited[i] = 0;
    }

    printf("\n=======SJF (Non-Preemptive)=======\n");
    printf("\n Gantt Chart\n");

    while(completed < n){
       int index = -1;
       int shortest = 999999;
       
       for(int i =0; i < n; i++){
          if(!visited[i] && processes[i].arrival_time <= currentTime &&
             processes[i].burst_time < shortest){
             shortest = processes[i].burst_time;
             index = i;
          }
       }

       if(index == 1){
        currentTime++;
        continue;
       }

         processes[index].start_time = RUNNING;

         processes[index].start_time = currentTime;
         processes[index].response_time = currentTime - processes[index].arrival_time;

         currentTime += processes[index].burst_time;

         processes[index].completion_time = currentTime;
         processes[index].turnaround_time = currentTime - processes[index].arrival_time;
         processes[index].waiting_time = processes[index].turnaround_time - processes[index].burst_time;

        processes[index].remaining_time = 0;
        processes[index].state = TERMINATED;
        visited[index] = 1;

        completed++;

        printf(" p%d | ", processes[index].pid);

    
    }

    printf("\n\n");

    printf("%-5s %-8s %-6s %-6s %-6s %-6s %-6s\n", "PID", "AT", "BT", "CT", "TAT", "WT", "RT");

    double totalWT = 0, totalTAT = 0, totalRT = 0;

    for(int i = 0; i < n ; i++){

        printf("%-5d %-8d %-6d %-6d %-6d %-6d %-6d\n", 
              processes[i].pid,
              processes[i].arrival_time,
              processes[i].burst_time, 
              processes[i].completion_time, 
              processes[i].turnaround_time, 
              processes[i].waiting_time, 
              processes[i].response_time);

        totalWT += processes[i].waiting_time;
        totalTAT += processes[i].turnaround_time;
        totalRT += processes[i].response_time;
    }


    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
    printf("Average Response Time: %.2f\n", totalRT / n);
}

