#include <stdio.h>
#include "m_statistics.h"

void calculateStatistics_m(M_PCB processes[], int n)
{

    for (int i = 0; i < n; i++)
    {
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;

        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
    }
}

void printStatistics_m(M_PCB processes[], int n, int cpuCount)
{

    double avgWT = 0.0;
    double avgTAT = 0.0;
    double avgRT = 0.0;

    int totalBurst = 0;
    int lastCompletion = 0;

    printf("\n===============================================\n");
    printf("              PROCESS STATISTICS\n");
    printf("===============================================\n");

    printf("%-5s %-5s %-5s %-5s %-5s %-5s\n",
           "PID",
           "CT",
           "TAT",
           "WT",
           "RT",
           "CPU");

    for (int i = 0 ; i < n; i++)
    {

        avgWT += processes[i].waitingTime;
        avgTAT += processes[i].turnaroundTime;
        avgRT += processes[i].responseTime;

        totalBurst += processes[i].burstTime;

        if (processes[i].completionTime > lastCompletion)
        {
            lastCompletion = processes[i].completionTime;
        }
    }

    avgWT /= n;
    avgTAT /= n;
    avgRT /= n;

    double cpuUtilization = 0.0;

    if (lastCompletion > 0)
    {
        cpuUtilization = ((double)totalBurst / ((double)lastCompletion * cpuCount)) * 100.0;
    }

    printf("\n-----------------------------------------------\n");
    printf("Average Waiting Time     : %.2f\n", avgWT);
    printf("Average Turnaround Time  : %.2f\n", avgTAT);
    printf("Average Response Time    : %.2f\n", avgRT);
    printf("CPU Utilization          : %.2f%%\n",
           cpuUtilization);
    printf("-----------------------------------------------\n");
}
