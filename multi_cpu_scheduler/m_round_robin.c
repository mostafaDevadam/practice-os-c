#include <stdio.h>
#include "m_queue.h"
#include "m_round_robin.h"
#include "m_gantt.h"
#include "m_statistics.h"

void roundRobinSchedule(M_PCB processes[], int n, CPU cpus[], int cpuCount, int quantum)
{

    Queue readyQueue;
    initQueue(&readyQueue);

    int completed = 0;
    int time = 0;

    initGantt_m();

    int slice[MAX_CPU] = {0};
    int sliceStart[MAX_CPU] = {0};

    while (completed < n)
    {

        // New arrivals
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime == time)
            {
                enqueue(&readyQueue, &processes[i]);
                processes[i].state = READY;
            }
        }

        // Assign idle CPUs
        for (int c = 0; c < cpuCount; c++)
        {
            if (!cpus[c].busy && !isEmpty(&readyQueue))
            {
                M_PCB *p = dequeue(&readyQueue);

                cpus[c].busy = 1;
                cpus[c].process = p;
                // cpus[c].process->startTime = time;

                slice[c] = 0;
                sliceStart[c] = time;

                if (p->responseTime == -1)
                {
                    p->responseTime = time - p->arrivalTime;
                }
            }
        }

        // Execute
        for (int c = 0; c < cpuCount; c++)
        {
            if (!cpus[c].busy)
            {
                continue;
            }

            M_PCB *p = cpus[c].process;

            p->remainingTime--;
            slice[c]++;

            // Process finished
            if (p->remainingTime == 0)
            {
                p->completionTime = time + 1;
                p->turnaroundTime = p->completionTime - p->arrivalTime;
                p->waitingTime = p->turnaroundTime - p->burstTime;

                p->state = TERMINATED;

                addGanttChart_m(c,
                                p->pid,
                                sliceStart[c],
                                time + 1);

                printf("Time %d : P%d finished on CPU %d\n",
                       time + 1,
                       p->pid,
                       c);

                cpus[c].busy = 0;
                cpus[c].process = NULL;

                slice[c] = 0;

                completed++;
            }
            // Quantum expired
            else if (slice[c] == quantum)
            {
                addGanttChart_m(c,
                                p->pid,
                                sliceStart[c],
                                time + 1);

                p->state = READY;

                enqueue(&readyQueue, p);

                cpus[c].busy = 0;
                cpus[c].process = NULL;

                slice[c] = 0;
            }
        }

        time++;
    }

    printf("\n=========================================\n");
    printf(" Round-Robin Scheduling Results\n");
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
