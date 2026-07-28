#include <string.h>
#include "disk.h"
#include "superblock.h"
#include <stdio.h>

SuperBlock sb;

int superblock_save(void)
{
    char buffer[BLOCK_SIZE];

    memset(buffer, 0, BLOCK_SIZE);

    memcpy(buffer, &sb, sizeof(SuperBlock));

    printf("Saving superblock:\n");
    printf("magic = %X\n", sb.magic);
    printf("total_inodes = %u\n", sb.total_inodes);

    return disk_write(1, buffer);
}

int superblock_load(void)
{

    char buffer[BLOCK_SIZE];

    if (disk_read(1, buffer) != 0)
        return -1;

    memcpy(&sb, buffer, sizeof(SuperBlock));

    printf("Loaded superblock:\n");
    printf("magic = %X\n", sb.magic);
    printf("total_inodes = %u\n", sb.total_inodes);

    if (sb.magic != FS_MAGIC)
        return -1;

    return 0;
}

int superblock_format(void)
{

     printf("=== superblock_format ===\n");

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

    printf("magic=%X total_inodes=%u\n",
           sb.magic,
           sb.total_inodes);

    return superblock_save();
}