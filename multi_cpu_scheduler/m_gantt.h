
#ifndef GANTT_H
#define GANTT_H

#define MAX_EVENTS 1000

typedef struct {
    int cpuID;
    int pid;
    int startTime;
    int endTime;

} GanttEvent;

void initGantt_m(void);

void addGanttChart_m(int cpuID, int pid, int startTime, int endTime);

void printGanttChart_m(int cpuCount);


#endif