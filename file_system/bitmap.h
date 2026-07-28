 
 #ifndef BITMAP_H
 #define BITMAP_H

 #include <stdint.h>

 #define MAX_BLOCKS 1024
 #define MAX_INODES 256

 int bitmap_init(void);

 int allocate_block(void);
 void free_block(uint32_t block);

 int allocate_inode(void);
 void free_inode(uint32_t inode);

 int bitmap_save(void);
 int bitmap_load(void);

 

 #endif