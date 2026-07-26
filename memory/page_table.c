#include <stdio.h>
#include "page_table.h"


PageTableEntry pageTable[NUMBER_OF_PAGES];
PageTableEntry page_table[NUMBER_OF_PAGES];

void initPageTable(void) {
    int i;
    for (i = 0; i < NUMBER_OF_PAGES; i++) {
        page_table[i].frame = -1;
        page_table[i].valid = 0;
    }
}

int getFrame(int pageNumber){
    if(pageNumber < 0 || pageNumber >= NUMBER_OF_PAGES){
        return -1;
    }

    if (pageTable[pageNumber].valid)
       return pageTable[pageNumber].frame;

    return -1;
}


void setFrame(int pageNumber, int frameNumber)
{
    if(pageNumber < 0 || pageNumber >= NUMBER_OF_PAGES){
        return;
    }

    pageTable[pageNumber].frame = frameNumber;
    pageTable[pageNumber].valid = 1;
}
void invalidatePage(int pageNumber){
     if(pageNumber < 0 || pageNumber >= NUMBER_OF_PAGES){
         return;
     }

     pageTable[pageNumber].frame = -1;
     pageTable[pageNumber].valid = 0;
}
int isPageValid(int pageNumber){
    if(pageNumber < 0 || pageNumber >= NUMBER_OF_PAGES){
        return 0;
    }
     
    
      return pageTable[pageNumber].valid;
}
void displayPageTable(void){
     int i;

     printf("\n===== Page Table====\n");
     printf("%-8s %-8s %-8s\n", "Page", "Frame", "Valid");
     printf("-------------------------\n");

     for(i = 0; i < NUMBER_OF_PAGES; i++){
        printf(
            "%-8d %-8d %-8d\n",
            i,
            pageTable[i].frame,
            pageTable[i].valid
        );
     }
}