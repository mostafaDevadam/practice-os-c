#include <string.h>
#include <stdio.h>
#include <time.h>
#include "inode.h"
#include "bitmap.h"
#include "superblock.h"
//#include "disk.h"
#include "cache.h"



#define INODES_PER_BLOCK (BLOCK_SIZE / sizeof(Inode))

int inode_init(void)
{
    char buffer[BLOCK_SIZE];

    memset(buffer, 0, BLOCK_SIZE);

    for (uint32_t i = 0; i < sb.inode_table_blocks; i++)
    {
        cache_write(sb.inode_table_start + i, buffer);
    }

    return 0;
}



int inode_read(uint32_t inode_number, Inode *inode)
{
    printf("inode_number = %u\n", inode_number);
    printf("total_inodes = %u\n", sb.total_inodes);

    if (inode_number >= sb.total_inodes)
    {
        printf("FAILED: inode_number >= total_inodes\n");
        return -1;
    }

    uint32_t block = sb.inode_table_start + (inode_number / INODES_PER_BLOCK);
    uint32_t index = inode_number % INODES_PER_BLOCK;

    printf("block = %u\n", block);
    printf("index = %u\n", index);

    char buffer[BLOCK_SIZE];

    int ret = cache_read(block, buffer);

    printf("cache_read returned %d\n", ret);

    if (ret != 0)
    {
        printf("FAILED: cache_read\n");
        return -1;
    }

    memcpy(inode, ((Inode *)buffer) + index, sizeof(Inode));

    printf("inode.id = %u\n", inode->id);

    return 0;
}




int inode_write(uint32_t inode_number, Inode *inode)
{

    if (inode_number >= sb.total_inodes)
    {
        return -1;
    }

    uint32_t block = sb.inode_table_start + inode_number / INODES_PER_BLOCK;
    uint32_t index = inode_number % INODES_PER_BLOCK;

    char buffer[BLOCK_SIZE];

    if (cache_read(block, buffer) != 0)
    {
        return -1;
    }

    memcpy(((Inode *)buffer) + index, inode, sizeof(Inode));

    return cache_write(block, buffer);
}

int inode_create(uint32_t type)
{

    int number = allocate_inode();

    if (number < 0)
    {
        return -1;
    }

    Inode inode;

    memset(&inode, 0, sizeof(Inode));

    inode.id = number;
    inode.type = type;
    inode.links = 1;

    inode.created = time(NULL);
    inode.modified = inode.created;

    inode_write(number, &inode);

    return number;
}

int inode_delete(uint32_t inode_number)
{

    Inode inode;

    if (inode_read(inode_number, &inode) != 0)
    {
        return -1;
    }

    for (int i = 0; i < DIRECT_POINTERS; i++)
    {
        if (inode.direct[i] != 0)
        {
            free_block(inode.direct[i]);
        }
    }

    if (inode.indirect != 0)
    {
        free_block(inode.indirect);
    }

    free_inode(inode_number);

    memset(&inode, 0, sizeof(Inode));

    inode_write(inode_number, &inode);

    return 0;
}
