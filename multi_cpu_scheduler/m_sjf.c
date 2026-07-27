#include <stdio.h>
#include "m_sjf.h"
#include "m_gantt.h"
#include "m_statistics.h"

void sjfSchedule(M_PCB processes[], int n, CPU cpus[], int cpuCount)
{

    int completed = 0;
    int time = 0;

    initGantt_m();

    while (completed < n)
    {

        // Assign shortest available job to each idle CPU
        for (int c = 0; c < cpuCount; c++)
        {

            if (!cpus[c].busy)
            {
                int index = -1;

                for (int i = 0; i < n; i++)
                {

                    if (processes[i].arrivalTime <= time &&
                        processes[i].remainingTime > 0 &&
                        processes[i].state == READY)
                    {
                        int running = 0;

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

                        if (index == -1 ||
                            processes[i].burstTime < processes[index].burstTime)
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
                    processes[index].startTime = time;

                    if (processes[index].responseTime == -1)
                    {
                        processes[index].responseTime = time - processes[index].arrivalTime;
                    }
                }
            }
        }

        // Execute
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

                    addGanttChart_m(c,
                                    p->pid,
                                    p->startTime,
                                    time + 1);

                    completed++;
                }
            }
        }

        time++;
    }

    printf("\n=========================================\n");
    printf(" SJF Scheduling Results\n");
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