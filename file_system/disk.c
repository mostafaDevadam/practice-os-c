#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disk.h"

static FILE *disk = NULL;

int disk_create(const char *filename){
    FILE *fp = fopen(filename, "wb");

    if(!fp){
        return -1;
    }

    char zero[BLOCK_SIZE];
    memset(zero, 0, BLOCK_SIZE);

    for(int i= 0; i < TOTAL_BLOCKS; i++){
        fwrite(zero, BLOCK_SIZE, 1, fp);
    }

    fclose(fp);
    return 0;
}

int disk_open(const char *filename){
    disk = fopen(filename, "rb+");
    if(!disk){
        return -1;
    }

    return 0;
}

void disk_close(void){
        if(disk){
            fclose(disk);
            disk = NULL;
        }
}


int disk_read(uint32_t block, void *buffer){

    if(!disk){
        return -1;
    }

    if(block >= TOTAL_BLOCKS){
        return -1;
    }

    fseek(disk, block * BLOCK_SIZE, SEEK_SET);
    return fread(buffer, BLOCK_SIZE, 1, disk) == 1 ?  0: -1;
    

}

int disk_write(uint32_t block, const void *buffer){

    if(!disk){
        return -1;
    }

    if(block >= TOTAL_BLOCKS){
        return -1;
    }

    fseek(disk, block * BLOCK_SIZE, SEEK_SET);
    return fwrite(buffer, BLOCK_SIZE, 1, disk) == 1 ?  0: -1;

}
