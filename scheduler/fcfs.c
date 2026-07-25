#include <stdio.h>
#include "pcb.h"
#include "fcfs.h"


void fcfs(PCB processes[], int n){

    int currentTime = 0;

    for(int i = 0; i < n - 1; i++){
       for(int j = i + 1; j < n; j++){
          if(processes[i].arrival_time > processes[j].arrival_time){
             PCB temp = processes[i];
             processes[i] = processes[j];
             processes[j] = temp;
          }
       }
    }

    printf("\n=======FCFS Scheduling=======\n");

    printf("\n Gnatt Chart: \n");


    for(int i = 0; i < n; i++){
        if(currentTime < processes[i].arrival_time){
            currentTime = processes[i].arrival_time;
        }
        
        processes[i].start_time = currentTime;
        processes[i].response_time = processes[i].start_time - processes[i].arrival_time;
        currentTime += processes[i].burst_time;

        processes[i].completion_time = currentTime;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        printf(" p%d | ", processes[i].pid);
    }

    printf("\n\n");

    printf("%-5s %-8s %-6s %-6s %-6s %-6s %-6s\n", "PID", "Arrival", "Burst", "CT", "TAT", "WT", "RT");


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

    printf("\nAverage Waiting Time: %.2f\n", totalWT/n);
    printf("Average Turnaround Time: %.2f\n", totalTAT/n);
    printf("Average Response Time: %.2f\n", totalRT/n);






}