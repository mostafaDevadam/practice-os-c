 
 #ifndef SUPERBLOCK_H
 #define SUPERBLOCK_H

 #include <stdint.h>

 #define FS_MAGIC 0x4D594653

 typedef struct {
    
    uint32_t magic;
    uint32_t block_size;
    uint32_t total_blocks;

    uint32_t inode_table_start;
    uint32_t inode_table_blocks;

    uint32_t block_bitmap;
    uint32_t inode_bitmap;

    uint32_t data_block_start;

    uint32_t total_inodes;

    uint32_t free_blocks;
    uint32_t free_inodes;


 } SuperBlock;


 int superblock_format(void);
 int superblock_load(void);
 int superblock_save(void);

 extern SuperBlock sb;

 #endif