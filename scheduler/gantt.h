
#define MAX_GANTT 200

typedef struct {
    int pid;
    int start;
    int end;


} GantEntry;


void addGanttEntry(int pid, int start, int end);
void printGanttChart(void);
void clearGanttChart(void);

