#ifndef PCB_H
#define PCB_H


typedef enum {
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
} ProcessState;


typedef struct PCB {

    int pid; // Process ID


    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority; // Process priority

    int program_counter; // Simulated program counter
    int stack_pointer; // Simulated stack pointer
    int registers[8]; // Simulated CPU registers

    ProcessState state;
  
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;

    struct PCB *next; // Pointer to the next PCB in the queue

} PCB;



void initializePCB(PCB *process, int pid, 
    int arrival, int burst, int priority);

void printPCB(const PCB *process);

const char *stateToString(ProcessState state);


#endif // PCB_H