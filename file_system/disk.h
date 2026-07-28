#ifndef DISK_H
#define DISK_H

#include <stdint.h>


#define BLOCK_SIZE 4096
#define TOTAL_BLOCKS 1024

int disk_create(const char *filename);
int disk_open(const char *filename);
void disk_close(void);

int disk_read(uint32_t block, void *buffer);
int disk_write(uint32_t block, const void *buffer);

#endif