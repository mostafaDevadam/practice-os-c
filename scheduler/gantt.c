#include <stdio.h>
#include "gantt.h"

static GantEntry chart[MAX_GANTT];
static int count = 0;

void clearGanttChart(void){
    count = 0;
}

void addGanttEntry(int pid, int start, int end){
    if(count > 0 && chart[count - 1].pid == pid && chart[count - 1].end == start){
        chart[count - 1].end = end;
        return;
    }

    chart[count].pid = pid;
    chart[count].start = start;
    chart[count].end = end;
    count++;

}

void printGanttChart(void){
    printf("\n========== Gantt Chart ========= \n");

    for(int i = 0; i < count; i++){
       
        printf("+----------");
    }
    printf("+\n");

    for(int i = 0; i < count; i++){
         if(chart[i].pid == 0)
              printf("| Idle ");
         else
              printf("| P%d ", chart[i].pid);
    }
    printf("|\n");

    for(int i = 0; i < count; i++){
        printf("+----------");
    }
    printf("+\n");

    printf("%d", chart[0].start);

    for(int i = 0; i < count; i++){
        printf("%d", chart[i].end);
    }
    printf("\n");


}