 #include <string.h>
 #include "disk.h"
 #include "superblock.h"

 SuperBlock sb;

 int superblock_save(void){
   char buffer[BLOCK_SIZE];

   memset(buffer, 0, BLOCK_SIZE);

   memcpy(buffer, &sb, sizeof(SuperBlock));

   return disk_write(1, buffer);

 }

 int superblock_load(void){

    char buffer[BLOCK_SIZE];

    if(disk_read(1, buffer) != 0){
        return -1;
    }

    memcpy(&sb, buffer, sizeof(SuperBlock));

    if(sb.magic != FS_MAGIC){
        return -1;
    }
       
    return 0;


 }

 int superblock_format(void){

    memset(&sb, 0, sizeof(sb));

    sb.magic = FS_MAGIC;
    sb.block_size = BLOCK_SIZE;
    sb.total_blocks = TOTAL_BLOCKS;

    sb.block_bitmap = 2;
    sb.inode_bitmap = 3;

    sb.inode_table_start = 4;
    sb.inode_table_blocks = 16;

    sb.data_block_start = 20;

    sb.total_inodes = 256;

    sb.free_blocks = TOTAL_BLOCKS - sb.data_block_start;
    sb.free_inodes = sb.total_inodes;

    return superblock_save();





 }