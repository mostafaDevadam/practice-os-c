

#include <stdio.h>
#include "m_fcfs.h"
#include "m_queue.h"
#include "m_gantt.h"
#include "m_statistics.h"

void fcfsSchedule(M_PCB processes[], int n, CPU cpus[], int cpuCount)
{

    Queue readyQueue;

    initQueue(&readyQueue);

    int completed = 0;
    int time = 0;

    initGantt_m();

    while (completed < n)
    {

        // Add newly arrived processes
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime == time)
            {
                processes[i].state = READY;
                enqueue(&readyQueue, &processes[i]);
            }
        }

        // Assign ready processes to idle CPUs
        for (int c = 0; c < cpuCount; c++)
        {
            if (!cpus[c].busy && !isEmpty(&readyQueue))
            {
                M_PCB *p = dequeue(&readyQueue);

                printf("p = %p\n", (void *)p);

                if (p == NULL)
                {
                    printf("NULL process!\n");
                    continue;
                }

                printf("PID = %d\n", p->pid);

                cpus[c].process = p;
                cpus[c].busy = 1;

                p->state = RUNNING;
                p->cpuID = c;
                p->startTime = time;

                if (p->responseTime == -1)
                {
                    p->responseTime = time - p->arrivalTime;
                }

                printf("Time %d : CPU %d -> P%d\n",
                       time,
                       c,
                       p->pid

                );
            }
        }

        // Execute one time unit
        for (int c = 0; c < cpuCount; c++)
        {
            if (cpus[c].busy)
            {
                M_PCB *p = cpus[c].process;

                p->remainingTime--;

                if (p->remainingTime == 0)
                {

                    p->completionTime = time + 1;
                    p->turnaroundTime = p->completionTime - p->arrivalTime;
                    p->waitingTime = p->turnaroundTime - p->burstTime;

                    p->state = TERMINATED;

                    printf(
                        "Time %d : p%d finished on CPU %d\n",
                        time + 1,
                        p->pid,
                        c);

                    cpus[c].busy = 0;
                    cpus[c].process = NULL;

                    completed++;

                    addGanttChart_m(c,
                                    p->pid,
                                    p->startTime,
                                    time + 1);
                }
            }
        }

        time++;
    }

    printf("\n=========================================\n");
    printf(" FCFS Scheduling Results\n");
    printf("===========================================\n");

    printf("PID\tCT\tTT\tWT\tRT\n");

    for (int i = 0; i < n; i++)
    {
        printf(
            "P%d\t%d\t%d\t%d\t%d\n",
            processes[i].pid,
            processes[i].completionTime,
            processes[i].turnaroundTime,
            processes[i].waitingTime,
            processes[i].responseTime

        );
    }

    printGanttChart_m(cpuCount);
    calculateStatistics_m(processes, n);
    printStatistics_m(processes, n, cpuCount);
}