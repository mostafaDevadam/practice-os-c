#include <stdio.h>
#include "pcb.h"

void initializePCB(PCB *process, int pid, int arrival, 
    int burst, int priority) {
    process->pid = pid;
    process->arrival_time = arrival;
    process->burst_time = burst;
    process->remaining_time = burst; // Initially, remaining time is equal to burst time
    process->priority = priority; // Set the priority

    process->program_counter = 0; // Initialize program counter
    process->stack_pointer = 0; // Initialize stack pointer

    for (int i = 0; i < 8; i++) {
        process->registers[i] = 0; // Initialize registers to zero
    }
    process->state = NEW; // Initial state is NEW

    process->start_time = -1; // Not started yet
    process->completion_time = -1; // Not completed yet
    process->turnaround_time = -1; // Not calculated yet
    process->waiting_time = -1; // Not calculated yet
    process->response_time = -1; // Not calculated yet
    process->next = NULL; // No next PCB in the queue initially
}

const char *stateToString(ProcessState state) {
    switch (state) {
        case NEW: return "NEW";
        case READY: return "READY";
        case RUNNING: return "RUNNING";
        case WAITING: return "WAITING";
        case TERMINATED: return "TERMINATED";
        default: return "UNKNOWN";
    }
}


void printPCB(const PCB *process) {

    printf("---------------------------------\n");
    printf("PID: %d\n", process->pid);
    printf("Arrival Time: %d\n", process->arrival_time);
    printf("Burst Time: %d\n", process->burst_time);
    printf("Remaining Time: %d\n", process->remaining_time);
    printf("Priority: %d\n", process->priority);

    printf("Program Counter: %d\n", process->program_counter);
    printf("Stack Pointer: %d\n", process->stack_pointer);

    printf("Registers: ");
    for (int i = 0; i < 8; i++) {
        printf("%d ", process->registers[i]);
    }
    printf("\n");
    
    printf("State: %s\n", stateToString(process->state));
    printf("Start Time: %d\n", process->start_time);
    printf("Completion Time: %d\n", process->completion_time);
    printf("Turnaround Time: %d\n", process->turnaround_time);
    printf("Waiting Time: %d\n", process->waiting_time);
    printf("Response Time: %d\n", process->response_time);
}