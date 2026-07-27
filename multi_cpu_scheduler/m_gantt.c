#include <stdio.h>
#include "m_gantt.h"

static GanttEvent events[MAX_EVENTS];
static int eventCount = 0;

void initGantt_m(void){
     eventCount = 0;
}

void addGanttChart_m(int cpuID, int pid, int startTime, int endTime){
     if(eventCount >= MAX_EVENTS) return;

     events[eventCount].cpuID = cpuID;
     events[eventCount].pid = pid;
     events[eventCount].startTime = startTime;
     events[eventCount].endTime = endTime;

     eventCount++;

}

void printGanttChart_m(int cpuCount){

    printf("\n==============================\n");
    printf("        GANTT CHART\n");
    printf("==============================\n");

    for(int cpu = 0; cpu < cpuCount; cpu++){
        printf("CPU %d: ", cpu);

        for(int i = 0; i < eventCount; i++){
            if(events[i].cpuID == cpu){
                printf("| P%d ", events[i].pid);
            }
        }

        printf("|\n");

        printf("       ");

        for(int i = 0; i < eventCount; i ++){
            if(events[i].cpuID == cpu){
                printf("%d ", events[i].startTime);
            }
        }

        if(eventCount > 0){
            printf("%d", events[eventCount - 1].endTime);
        }

        printf("\n\n");



    }




}
