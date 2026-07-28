#include <string.h>
#include "disk.h"
#include "bitmap.h"
#include "superblock.h"


static uint8_t block_bitmap[MAX_BLOCKS];
static uint8_t inode_bitmap[MAX_INODES];

int bitmap_save(void)
{
    char buffer[BLOCK_SIZE];

    memset(buffer, 0, BLOCK_SIZE);
    memcpy(buffer, block_bitmap, sizeof(block_bitmap));

    if(disk_write(sb.block_bitmap, buffer) != 0){
        return -1;
    }

    memset(buffer, 0, BLOCK_SIZE);
    memcpy(buffer, inode_bitmap, sizeof(inode_bitmap));

    return disk_write(sb.inode_bitmap, buffer);
}

int allocate_block(void)
{
    for(uint32_t i = sb.data_block_start; i < MAX_BLOCKS; i++){

        if(block_bitmap[i] == 0){
            block_bitmap[i] = 1;
            sb.free_blocks--;
            bitmap_save();
            superblock_save();
            return i;
        }
        
    }
    return -1;
}

void free_block(uint32_t block)
{
    if(block >= MAX_BLOCKS){
        return;
    }

    if(block_bitmap[block]){

        block_bitmap[block] = 0;
        sb.free_blocks++;
        bitmap_save();
        superblock_save();
        
    }
}

int allocate_inode(void)
{
    for(uint32_t i = 0; i < MAX_INODES; i++){
        if(inode_bitmap[i] == 0){
            inode_bitmap[i] = 1;
            sb.free_inodes--;
            bitmap_save();
            superblock_save();
            return i;
        }
    }

    return -1;
}

void free_inode(uint32_t inode)
{
    if(inode >= MAX_INODES){
        return;
    }

    if(inode_bitmap[inode]){
        inode_bitmap[inode] = 0;
        sb.free_inodes++;
        bitmap_save();
        superblock_save();
    }
}

int bitmap_init(void)
{
    memset(block_bitmap, 0, sizeof(block_bitmap));
    memset(inode_bitmap, 0, sizeof(inode_bitmap));

    for(uint32_t i = 0; i < sb.data_block_start; i++){
        block_bitmap[i] = 1;
    }

    return bitmap_save();
}

int bitmap_load(void)
{

    char buffer[BLOCK_SIZE];

    if(disk_read(sb.block_bitmap, buffer) != 0){
        return -1;
    }

    memcpy(block_bitmap, buffer, sizeof(block_bitmap));

    if(disk_read(sb.inode_bitmap, buffer) != 0){
        return -1;
    }

    memcpy(inode_bitmap, buffer, sizeof(inode_bitmap));

    return 0;
}
