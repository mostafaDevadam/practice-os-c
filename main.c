#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/shell.h"
#include "scheduler/pcb.h"
#include "scheduler/fcfs.h"
#include "scheduler/scheduler.h"
#include "memory/memory.h"
#include "memory/mem_statistics.h"
#include "memory/page_table.h"
#include "memory/tlb.h"
#include "memory/replacement.h"
#include "memory/mem_statistics.h"
#include "concurrency/producer_consumer.h"
#include "concurrency/dining_philosophers.h"
#include "concurrency/readers_writers.h"
#include "concurrency/sleeping_barber.h"
#include "concurrency/utils.h"
#include "deadlock/banker.h"
#include "deadlock/detection.h"
#include "deadlock/avoidance.h"
#include "deadlock/display.h"
#include "deadlock/prevention.h"
#include "deadlock/input.h"
#include "deadlock/utils_d.h"
#include "multi_cpu_scheduler/m_scheduler.h"
#include "multi_cpu_scheduler/m_pcb.h"
#include "multi_cpu_scheduler/m_cpu.h"
#include "multi_cpu_scheduler/m_utils.h"
#include "multi_cpu_scheduler/m_input.h"
#include "file_system/disk.h"
#include "file_system/superblock.h"
#include "file_system/bitmap.h"
#include "file_system/inode.h"
#include "file_system/directory.h"


void initMemorySystem()
{
    generateBackingStore();
    // invalidateTLBEntry();
    initMemory();
    initPageTable();
    initTLB();
    initReplacement();
    initStatistics();
}

void translateAddresses(void)
{
    printf("\nAddress trasnlation is not implemented yet\n");
    printf("Later this fucntion will:\n");
    printf("- Read addresses.txt\n");
    printf("- Check TLB\n");
    printf("- Check Page Table\n");
    printf("- Handle Page Faults\n");
    printf("- Load pages from BACKING_STORE.bin\n");
    printf("- Display logical and physical addresses\n");
}

void demo_scheduler()
{
    /*
   // pcb
   PCB p1;
   initializePCB(&p1, 1, 0, 5, 1);
   p1.state = READY;
   printPCB(&p1);

   // fcfs
   PCB processes[] = {
       {1, 0, 5, 5, 1, 0, 0, {0}, NEW, -1, -1, -1, -1, -1, NULL},
       {2, 2, 3, 3, 2, 0, 0, {0}, NEW, -1, -1, -1, -1, -1, NULL},
       {3, 4, 2, 2, 3, 0, 0, {0}, NEW, -1, -1, -1, -1, -1, NULL},
       {4, 6, 4, 4, 4, 0, 0, {0}, NEW, -1, -1, -1, -1, -1, NULL}

   };
   int n = sizeof(processes) / sizeof(processes[0]);
   fcfs(processes, n);

   // sjf
   PCB processes_sjf[4];
   initializePCB(&processes_sjf[0], 1, 0, 8, 2);
   initializePCB(&processes_sjf[1], 2, 1, 4, 1);
   initializePCB(&processes_sjf[2], 3, 2, 9, 3);
   initializePCB(&processes_sjf[3], 4, 3, 5, 2);
   int n_ = 4;
   sjf(processes_sjf, n_);

   // srtf
   PCB processes_srtf[4];
   initializePCB(&processes_srtf[0], 1, 0, 8, 2);
   initializePCB(&processes_srtf[1], 2, 1, 4, 1);
   initializePCB(&processes_srtf[2], 3, 2, 9, 3);
   initializePCB(&processes_srtf[3], 4, 3, 5, 2);
   srtf(processes_srtf, 4);

   // priority
   PCB processes_pr[4];
   initializePCB(&processes_pr[0], 1, 0, 8, 2);
   initializePCB(&processes_pr[1], 2, 1, 4, 1);
   initializePCB(&processes_pr[2], 3, 2, 9, 3);
   initializePCB(&processes_pr[3], 4, 3, 5, 2);
   priorityScheduling(processes_pr, 4);

   // round robin
   PCB processes_rr[4];
   initializePCB(&processes_rr[0], 1, 0, 8, 2);
   initializePCB(&processes_rr[1], 2, 1, 4, 1);
   initializePCB(&processes_rr[2], 3, 2, 9, 3);
   initializePCB(&processes_rr[3], 4, 3, 5, 2);
   roundRobin(processes_rr, 4, 2);
   */
}
void shell_scheduler()
{

    int n, choice, quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    PCB processes[n];

    for (int i = 0; i < n; i++)
    {
        int at, bt, priority;

        printf("\nProcess %d\n", i + 1);

        printf("Arrival Time:");
        scanf("%d", &at);

        printf("Burst Time:");
        scanf("%d", &bt);

        printf("Priority:");
        scanf("%d", &priority);

        initializePCB(&processes[i], i + 1, at, bt, priority);
    }

    do
    {

        printf("\n===================================================\n");
        printf("   CPU Scheduling Simulator   \n");
        printf("---------------------------------------------------\n");
        printf("1. First Come First Serve (FCFS)\n");
        printf("2. Shortest Job First (SJF)\n");
        printf("3. Shortest Remaining Time First (SRTF)\n");
        printf("4. Priority Scheduling\n");
        printf("5. Round Robin\n");
        printf("0. Exit\n");
        printf("---------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {

        case 1:
            fcfs(processes, n);
            break;

        case 2:
            sjf(processes, n);
            break;

        case 3:
            srtf(processes, n);
            break;

        case 4:
            priorityScheduling(processes, n);
            break;

        case 5:
            printf("Enter Time Quantum: ");
            scanf("%d", &quantum);
            roundRobin(processes, n, quantum);
            break;

        case 0:
            printf("Goodbye!\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);
}

void shell_memory()
{
    int choice;
    initMemorySystem();

    do
    {

        printf("\n========================\n");
        printf(" Virtual Memory Simulator");
        printf("=========================\n");
        printf("1. Translate Addresses\n");
        printf("2. Display Page Table\n");
        printf("3. Display TLB\n");
        printf("4. Display Physical Memory\n");
        printf("5. Show Statistics\n");
        printf("6. Reset\n");
        printf("0. Exit\n");

        printf("\nChoice:");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            translateAddresses();
            break;
        case 2:
            displayPageTable();
            break;
        case 3:
            displayTLB();
            break;
        case 4:
            displayMemory();
            break;
        case 5:
            displayStatistics();
            break;
        case 6:
            initMemorySystem();
            break;
        case 0:
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);
}

void displayConcurrencyMenu()
{
    printf("\n");
    printf("=================================\n");
    printf("   OS Concurrency Simulator\n");
    printf("=================================\n");
    printf("1. Producer-Consumer\n");
    printf("2. Dining Philosophers\n");
    printf("3. Readers-Writers\n");
    printf("4. Sleeping Barber\n");
    printf("5. Exit\n");
    printf("=================================\n");
    printf("Enter your choice: ");
}
void shell_concurrency()
{
    int choice;

    initRandom();

    while (1)
    {
        displayConcurrencyMenu();

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please try again.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (choice)
        {
        case 1:
            printf("\n-----Producer-Consumer \n");
            producerConsumer();
            break;

        case 2:
            printf("\n-----Dining Philosophers \n");
            diningPhilosophers();
            break;

        case 3:
            printf("\n-----Readers-Writers \n");
            readersWriters();
            break;

        case 4:
            printf("\n-----Sleeping Barber \n");
            sleepingBarber();
            break;

        case 5:
            destroyUtils();
            printf("Goodbye!\n");
            // exit(0);
            break;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }

        printf("\nPress Enter to continue...");
        // while(getchar() != '\n');
        // getchar();
    }
}

void shell_deadlock()
{
    SystemState sys = {0};

    int choice;
    int initialized = 0;

    int process;

    while (1)
    {

        printf("\n=============================\n");
        printf(" Deadlock Management System\n");
        printf("=============================\n");
        printf("1. Enter System Data\n");
        printf("2. Display System State\n");
        printf("3. Calculate Need Matrix\n");
        printf("4. Check Safe State (Banker's)\n");
        printf("5. Resource Request\n");
        printf("6. Deadlock Detection\n");
        printf("7. Deadlock Prevention Check\n");
        printf("8. Release Resources\n");
        printf("9. Exit\n");

        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            inputSystemState(&sys);
            initialized = 1;

            break;
        case 2:
            if (initialized)
            {
                displaySystemState(&sys);
            }
            else
            {
                printf("Enter system data first.\n");
            }

            break;
        case 3:
            if (initialized)
            {

                calculateNeed(&sys);

                printf("calculateNeed finished\n");
            }
            else
            {
                printf("Enter system data first.\n");
            }

            break;
        case 4:
            if (initialized)
            {
                int sequence[MAX_PROCESS];
                if (avoidDeadlock(&sys, sequence))
                {
                    printf("Safe State.\n");
                    printSafeSequence_d(sequence, sys.processes);
                }
                else
                {
                    printf("System is not safe.\n");
                }
            }

            break;
        case 5:

            int request[MAX_RESOURCE];

            printf("Enter process number:");
            scanf("%d", &process);

            printf("Enter resource request:\n");

            for (int i = 0; i < sys.resources; i++)
            {
                printf("R%d: ", i);
                scanf("%d", &request[i]);
            }
            avoidRequest(&sys, process, request);
            break;
        case 6:
            int deadlocked[MAX_PROCESS];
            int count = detectDeadlock(&sys, deadlocked);
            printDeadlockProcesses(deadlocked, count);
            break;
        case 7:

            printf("Enter process number:");
            scanf("%d", &process);

            printf("Enter request:\n");

            for (int i = 0; i < sys.resources; i++)
            {
                scanf("%d", &request[i]);
            }

            preventRequest(&sys, process, request);

            break;

        case 8:
            printf("Enter process number:");
            scanf("%d", &process);

            releaseResources_d(&sys, process);
            resetProcessOrder(process);

            break;

        case 9:
            printf("Existing...\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
}

void run_multi_cpu_scheduler()
{

    printf("run_multi_cpu_scheduler\n");

    // int n = 5;

    /*M_PCB processes[5] =
        {

            {1, 0, 5, 5, 2, 0, 0, 0, -1, READY, -1},
            {2, 1, 3, 3, 1, 0, 0, 0, -1, READY, -1},
            {3, 2, 8, 8, 3, 0, 0, 0, -1, READY, -1},
            {4, 3, 4, 4, 2, 0, 0, 0, -1, READY, -1},
            {5, 5, 2, 2, 1, 0, 0, 0, -1, READY, -1}
        };*/

    M_PCB processes[MAX_PROCESSES];
    int cpuCount;
    int n = loadProcesses("multi_cpu_scheduler/processes.txt", processes, &cpuCount);

    if (n == -1)
    {
        return;
    }

    CPU cpus[MAX_CPU];

    initializeCPUs(cpus, cpuCount);
    // schedule(processes, n, cpus, cpuCount);

    printf("processes = %p\n", (void *)processes);
    printf("n = %d\n", n);
    printf("cpuCount = %d\n", cpuCount);

    // schedule_fcfs(processes, n, cpus, cpuCount);

    schedule_all(processes, n, cpus, cpuCount);

    printProcessTable(processes, n);

    printCPUStatus(cpus, 2);

    for (int i = 0; i < n; i++)
    {
        m_printPCB(processes[i]);
    }
}

void run_file_system()
{

    if (disk_create("disk.img") != 0)
    {
        printf("Failed to create disk\n");
        return;
    }

    if (disk_open("disk.img") != 0)
    {
        printf("Failed to open disk\n");
        return;
    }

    /*char buffer[BLOCK_SIZE];

    memset(buffer, 0, BLOCK_SIZE);
    strcpy(buffer, "Hello File System!");

    disk_write(5, buffer);

    // clear ram buffer
    memset(buffer, 0, BLOCK_SIZE);

    disk_read(5, buffer);

    printf("disk buffer: %s\n", buffer);*/

    if (superblock_format() != 0)
    {
        printf("Format failed\n");
        return;
    }

    if (superblock_load() != 0)
    {
        printf("Load failed\n");
        return;
    }

    bitmap_init();
    /*bitmap_load();

    int block = allocate_block();
    int inode_b = allocate_inode();*/

    inode_init();

    int id = inode_create(INODE_FILE);

    Inode inode;

    inode_read(id, &inode);

    //

    directory_init();
    int file = inode_create(INODE_FILE);
    directory_add(0, "hello.txt", file);
    directory_list(0);

     printf("\n----------Directory-----------------\n");

     printf("\nSearch result: inode %d\n", directory_find(0, "hello.txt"));

     directory_remove(0, "hello.txt");

    printf("\nAfter Directory deletion: \n");
     directory_list(0);

    

    




    printf("\n----------iNode-----------------\n");

    printf("ID: %d\n", inode.id);
    printf("Type: %d\n", inode.type);
    printf("Links: %d\n", inode.links);
    printf("Size: %d\n", inode.size);
    //printf("Created: %s\n", ctime(&inode.created));
    //printf("Modified: %s\n", ctime(&inode.modified));



    printf("\n----------Bitmap-----------------\n");

   /* printf("Allocated Block: %d\n", block);
    printf("Allcoated Inode : %d\n", inode_b);

    printf("Free Blocks : %u\n", sb.free_blocks);
    printf("Free Inodes : %u\n", sb.free_inodes);



    free_block(block);
    free_inode(inode_b);

    printf("\nafter Free:\n");
    printf("Free Blocks: %u\n", sb.free_blocks);
    printf("Free Inodes: %u\n", sb.free_inodes);*/

    printf("\n------------Disk---------------\n");

    printf("Magic : %X\n", sb.magic);
    printf("Block Size : %u\n", sb.block_size);
    printf("Total Blocks : %u\n", sb.total_blocks);
    printf("Data Starts : %u\n", sb.data_block_start);

    //

    

    inode_delete(id);

    

    disk_close();
}

int main()
{
    printf("Hello, World!\n");

    run_file_system();

    return 0;
}