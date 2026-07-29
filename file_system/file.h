#ifndef FILE_H
#define FILE_H

#include <stdint.h>

#define MAX_OPEN_FILES 32


typedef struct {
   int used;
   uint32_t inode;
   uint32_t offset;
} FileDescriptor;


int file_init(void);

int file_create(uint32_t parent_inode,const char *name);

int file_delete(uint32_t parent_inode, const char *name);

//int file_open(const char *name);
int file_open(uint32_t inode_number);

int file_close(int fd);

int file_read(int fd, void *buffer, uint32_t size);

int file_write(int fd, const void *buffer, uint32_t size);

int file_seek(int fd, uint32_t offset);



#endif