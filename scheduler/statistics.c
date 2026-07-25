#include <stdio.h>
#include "statistics.h"

void calculateStatistics(PCB processes[], int n)
{

    for (int i = 0; i < n; i++)
    {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        processes[i].response_time = processes[i].start_time - processes[i].arrival_time;
    }
}

void printStatistics(PCB processes[], int n)
{
    double totalWT, totalTAT, totalRT = 0;

    printf("\n====================================\n");
    printf(
        "",
        "PID", "AT", "BT", "CT", "WT", "RT", "PR");
    printf("\n====================================\n");

    for (int i = 0; i < n; i++)
    {
        printf(
            "%-5d %-5d %-5d %-5d %-5d %-5d %-5d %-5d %-5d %-5d %-5d \n",
            processes[i].pid,
            processes[i].arrival_time,
            processes[i].burst_time,
            processes[i].completion_time,
            processes[i].turnaround_time,
            processes[i].waiting_time,
            processes[i].response_time,
            processes[i].priority);

        totalWT += processes[i].waiting_time;
        totalTAT += processes[i].turnaround_time;
        totalRT += processes[i].response_time;    
    }

    printf("==========================================");
    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
    printf("\nAverage Response Time: %.2f\n", totalRT / n);
}