 #include <stdio.h>
 #include "tlb.h"

 TLBEntry tlb[TLB_SIZE];
 int tlbIndex = 0;

 void initTLB(void){
     int i;
     for(i = 0; i < TLB_SIZE; i++){
         tlb[i].page = -1;
         tlb[i].frame = -1;
     }

     tlbIndex = 0;
 }


int searchTLB(int pageNumber){

    int i;

    for(i = 0; i < TLB_SIZE; i++){
        if(tlb[i].page == pageNumber){
            return tlb[i].frame;
        }
    }

    return -1;

}

void addToTLB(int pageNumber, int frameNumber){
    tlb[tlbIndex].page = pageNumber;
    tlb[tlbIndex].frame = frameNumber;

    tlbIndex = (tlbIndex + 1) % TLB_SIZE;
}

void displayTLB(void){

    int i;

    printf("\n=========== TLB ==========\n");
    printf("%-6s %-8s %-8s \n", "Entry", "Page", "Frame");
    printf("----------------------------\n");

    
    for(i = 0; i < TLB_SIZE; i++){
        printf("%-6d %-8d %-8d\n", i, tlb[i].page, tlb[i].frame);
    }   

}


void invalidateTLBEntry(int pageNumber){
     int i;

     for(i = 0; i < TLB_SIZE; i++){
         if(tlb[i].page == pageNumber){
             tlb[i].page = -1;
             tlb[i].frame = -1;
             return;
         }
     }
}
