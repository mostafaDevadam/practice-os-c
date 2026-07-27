#include <stdio.h>
#include "m_scheduler.h"

void schedule(M_PCB processes[], int n, CPU cpus[], int cpuCount)
{
    int completed = 0;
    int time = 0;

    while (completed < n)
    {
        /* Assign ready processes to idle CPUs */
        for (int c = 0; c < cpuCount; c++)
        {
            if (!cpus[c].busy)
            {
                for (int i = 0; i < n; i++)
                {
                    if (processes[i].arrivalTime <= time &&
                        processes[i].remainingTime > 0 &&
                        processes[i].state == READY)
                    {
                        int assigned = 0;

                        /* Check whether this process is already on another CPU */
                        for (int k = 0; k < cpuCount; k++)
                        {
                            if (cpus[k].busy &&
                                cpus[k].process == &processes[i])
                            {
                                assigned = 1;
                                break;
                            }
                        }

                        if (!assigned)
                        {
                            cpus[c].busy = 1;
                            cpus[c].process = &processes[i];

                            processes[i].state = RUNNING;
                            processes[i].cpuID = c;

                            if (processes[i].responseTime == -1)
                            {
                                processes[i].responseTime =
                                    time - processes[i].arrivalTime;
                            }

                            printf("Time %d: CPU %d -> P%d\n",
                                   time,
                                   c,
                                   processes[i].pid);

                            break;
                        }
                    }
                }
            }
        }

        /* Execute one time unit */
        for (int c = 0; c < cpuCount; c++)
        {
            if (cpus[c].busy)
            {
                M_PCB *p = cpus[c].process;

                p->remainingTime--;

                if (p->remainingTime == 0)
                {
                    p->completionTime = time + 1;
                    p->turnaroundTime =
                        p->completionTime - p->arrivalTime;
                    p->waitingTime =
                        p->turnaroundTime - p->burstTime;

                    p->state = TERMINATED;

                    printf("Time %d: P%d finished on CPU %d\n",
                           time + 1,
                           p->pid,
                           c);

                    cpus[c].busy = 0;
                    cpus[c].process = NULL;

                    completed++;
                }
            }
        }

        time++;
    }

    printf("\n==============================\n");
    printf("Process Statistics\n");
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