#include <stdio.h>
#include <string.h>
#include "memory.h"

char physicalMemory[NUMBER_OF_FRAMS][PAGE_SIZE];

void initMemory(void){
   memset(physicalMemory, 0, sizeof(physicalMemory));
}

void loadPage(int frameNumber, char *buffer){
    if(frameNumber < 0 || frameNumber >= NUMBER_OF_FRAMS){
        return;
    }

    memcpy(physicalMemory[frameNumber], buffer, PAGE_SIZE);
}

char readyByte(int frameNumber, int offset){
    if(frameNumber < 0 || frameNumber >= NUMBER_OF_FRAMS){
        return 0; 
    }

    if (offset < 0 || offset >= PAGE_SIZE)
       return 0;

    return physicalMemory[frameNumber][offset];
}

void writeByte(int frameNumber, int offset, char value){
     if(frameNumber < 0 || frameNumber >= NUMBER_OF_FRAMS){
         return;
     }

     if (offset < 0 || offset >= PAGE_SIZE)
        return;
    
    physicalMemory[frameNumber][offset] = value;    
}

void displayMemory(void){

    int frame, offset;

    printf("\n========== Physical Memory =================\n");

    for(frame = 0; frame < NUMBER_OF_FRAMS; frame++){
        printf("Frame %3d : \n", frame);
        for(offset = 0; offset < PAGE_SIZE; offset++){
            printf("%c", physicalMemory[frame][offset]);
        }
        printf("\n");
    }

}

int loadPageFromBackingStore(int pageNumber, int frameNumber){
    FILE *fp;
    char buffer[PAGE_SIZE];

    fp = fopen("BACKING_STORE.bin", "rb");

    if(fp == NULL){
        return 0;
    }

    fseek(fp, pageNumber * PAGE_SIZE, SEEK_SET);

    if(fread(buffer, sizeof(char), PAGE_SIZE, fp) != PAGE_SIZE){
        fclose(fp);
        return 0;
    }

    fclose(fp);

    loadPage(frameNumber, buffer);
    
    return 1;
}