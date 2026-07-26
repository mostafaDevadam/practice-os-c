#include <stdio.h>
#include "mem_statistics.h"

static int totalAddresses;
static int tlbHits;
static int tlbMisses;
static int pageFaults;


void initStatistics(void){

    totalAddresses = 0;
    tlbHits = 0;
    tlbMisses = 0;
    pageFaults = 0;
}

void incrementAddresses(void){
     totalAddresses++;

}

void incrementTLBHits(void){
    tlbHits++;
}

void incrementTLBMisses(void){
    tlbMisses++;

}

void incrementPageFaults(void){
    pageFaults++;

}

void displayStatistics(void){
     double tlbHitRatio = 0.0;
     double pageFaultRate = 0.0;

     if(totalAddresses > 0){
        tlbHitRatio = ((double)tlbHits / (double)totalAddresses) * 100.0;
        pageFaultRate = ((double)pageFaults / (double)totalAddresses) * 100.0;

        printf("\n======== Memory Statistcs ======\n");
        printf("\n\nTotal Addresses: %d\n", totalAddresses);
        printf("TLB Hits: %d\n", tlbHits);
        printf("TLB Misses: %d\n", tlbMisses);
        printf("Page Faults: %d\n", pageFaults);
        printf("TLB Hit Ratio: %.2f%%\n", tlbHitRatio);
        printf("Page Fault Rate: %.2f%%\n", pageFaultRate);
     }

}