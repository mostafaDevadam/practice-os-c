#include <stdio.h>
#include "m_priority.h"

void prioritySchedule(M_PCB processes[], int n, CPU cpus[], int cpuCount)
{

    int completed = 0;
    int time = 0;

    while (completed < n)
    {
        // assign highest-priority process to idle CPUs
        for (int c = 0; c < cpuCount; c++)
        {
            if (!cpus[c].busy)
            {
                int index = -1;

                for (int i = 0; i < n; i++)
                {

                    if (processes[i].arrivalTime <= time &&
                        processes[i].remainingTime > 0 &&
                        processes[i].state != RUNNING)
                    {
                        int running = 0;
                        // Check if already running
                        for (int k = 0; k < cpuCount; k++)
                        {

                            if (cpus[k].busy && cpus[k].process == &processes[i])
                            {
                                running = 1;
                                break;
                            }
                        }

                        if (running)
                        {
                            continue;
                        }

                        // Lower number = Higher priority
                        if (index == -1 || processes[i].priority < processes[index].priority)
                        {
                            index = i;
                        }
                        // Tie-breaker: Earlier arrival time
                        else if (
                            processes[i].priority == processes[index].priority &&
                            processes[i].arrivalTime < processes[index].arrivalTime)
                        {
                            index = i;
                        }
                    }
                }

                if (index != -1)
                {
                    cpus[c].busy = 1;
                    cpus[c].process = &processes[index];

                    processes[index].state = RUNNING;
                    processes[index].cpuID = c;

                    if (processes[index].responseTime == -1)
                    {
                        processes[index].responseTime = time - processes[index].arrivalTime;
                    }

                    printf(
                        "Time %d : CPU %d -> P%d (Priority %d)\n",
                        time,
                        c,
                        processes[index].pid,
                        processes[index].priority

                    );
                }
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

                      cpus[c].busy = 0;
                      cpus[c].process = NULL;

                      completed++;
                    }
            }
        }

        time++;
    }

    printf("\n==============================\n");
    printf(" Priority Scheduling Results\n");
    printf("==============================\n");

    printf("PID\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               processes[i].pid,
               processes[i].completionTime,
               processes[i].turnaroundTime,
               processes[i].waitingTime,
               processes[i].responseTime);
    }
}